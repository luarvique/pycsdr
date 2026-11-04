import array
import math
import threading
import unittest

from pycsdr.modules import Buffer, FskUartDecoder, Module
from pycsdr.types import Format


class FskUartTest(unittest.TestCase):
    def testInvalidArguments(self):
        for args, kwargs in (
            ((0,), {}), ((-1,), {}), ((12000,), {'baudRate': 0}),
            ((12000,), {'baudRate': float('nan')}),
            ((12000,), {'markFreq': float('inf')}),
            ((12000,), {'spaceFreq': 6000}),
            ((12000,), {'gapChars': -1}),
            ((12000,), {'maxFrame': 0}), ((12000,), {'maxFrame': -1}),
            ((12000,), {'maxFrame': 4097}),
        ):
            with self.subTest(args=args, kwargs=kwargs):
                with self.assertRaises(ValueError):
                    FskUartDecoder(*args, **kwargs)

    def testNativeBuffers(self):
        payload = b'\x00\x0d\xff\x01\x55'
        bits = [1] * 120
        for byte in payload:
            bits.extend([0] + [(byte >> i) & 1 for i in range(8)] + [1])
        bits.extend([1] * 120)
        audio = array.array('f')
        phase = 0
        for bit in bits:
            for _ in range(10):
                phase += 2 * math.pi * (1300 if bit else 2100) / 12000
                audio.append(0.5 * math.sin(phase))
        source, sink = Buffer(Format.FLOAT), Buffer(Format.CHAR)
        reader = sink.getReader()
        decoder = FskUartDecoder(sampleRate=12000)
        self.assertIsInstance(decoder, Module)
        self.assertEqual(decoder.getInputFormat(), Format.FLOAT)
        self.assertEqual(decoder.getOutputFormat(), Format.CHAR)
        lines, errors = [], []
        completed = threading.Event()

        def collect():
            data = b''
            try:
                while True:
                    block = reader.read()
                    if block is None:
                        return
                    data += block.tobytes()
                    while b'\n' in data:
                        line, data = data.split(b'\n', 1)
                        lines.append(line)
                        if line.split()[2] == payload.hex().encode():
                            completed.set()
                            return
            except Exception as error:
                errors.append(error)
                completed.set()

        thread = threading.Thread(target=collect, daemon=True)
        thread.start()
        try:
            decoder.setReader(source.getReader())
            decoder.setWriter(sink)
            source.write(audio.tobytes())
            self.assertTrue(completed.wait(5), 'native worker did not produce a frame')
            self.assertEqual(errors, [])
            self.assertTrue(any(line.split()[2] == payload.hex().encode() for line in lines))
        finally:
            decoder.stop()
            reader.stop()
            thread.join(2)
        self.assertFalse(thread.is_alive())


if __name__ == '__main__':
    unittest.main()
