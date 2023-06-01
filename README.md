# A simple LPC speech encoder

Uses [Praat](https://www.fon.hum.uva.nl/praat/) to get
LPC coefficients and convert them to C structures/arrays.
The output data is small enough and the decoding is simple
enough to be performed even on small embedded platforms.

1. Run the Python conversion script.

   ```
   python3 generate.py
   ```

   The output will be two files: `lpc_data.c` and `lpc_data.h`.
   The generated phrases/words are in the `data` list, in the
   `generate.py` script.

2. Build the example decoder application:

   ```
   cd decoder
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run the application:

   ```
   ./decoder_test | play -r 11000 -c 1 -b 16 -t s16 -
   ```
   or
   ```
   ./decoder_test | sox -r 11000 -c 1 -t s16 - out.wav
   ```
   to export to .wav file
