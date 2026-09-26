# FSK/UART binding

- Build against CSDR providing `csdr/fskuart.hpp` and `Csdr::FskUartDecoder`.
- Keep this a thin binding, matching the RTTY/SITOR-B module pattern. All
  per-sample DSP, timing and UART state belong in CSDR.
- Reject invalid/non-finite parameters as Python exceptions; no C++ exception
  may escape the constructor. Include a construction-failure test.
- Verify real buffers and the native worker thread, not an import-only stub.
- Run `python3 -m unittest discover -s tests -v` after building the extension;
  ensure the runtime library path points at the matching CSDR build.
