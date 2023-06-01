#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <math.h>
#include <assert.h>
#include <limits.h>

#include "lpc.h"
#include "lpc_data.h"

int main(int argc, char *argv[])
{
    lpc_filter_t *f = lpc_filter_new();
    assert(f);

    lpc_seq_decoder_t *dec = lpc_seq_decoder_new();
    assert(dec);

    for (size_t i = 0; i < LPC_MAX_SEQ; i++)
    {
        lpc_seq_t const *s[1] = {lpc_get_seq(i)};
        size_t all = lpc_seq_decoder_update(dec, (const lpc_seq_t *const *)&s, 1);

        {
            bool finished = false;
            size_t samples = 0;
            fix16_t y;
            int16_t buf_out[all];

            while (!finished)
            {
                uint32_t rnd = rand();
                finished = lpc_seq_decoder_exec(dec, rnd, &y);
                buf_out[samples++] = (int64_t)y * INT16_MAX / (8 * FIX_ONE);
            }

            size_t written = fwrite(buf_out, 2, all, stdout);
            assert(written == all);
            fflush(stdout);
        }
    }

    exit(EXIT_SUCCESS);
}
