#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <math.h>
#include <assert.h>
#include <limits.h>

#include "lpc.h"
#include "lpc_data.h"

static const float taps[40] = {
    0.0004984330412411764, 0.0013628123002057632, 0.0017376237448470013, 0.0009770267293160936, -0.0013501901565744464,
    -0.004477466799346431, -0.006055013116446954, -0.0033318393261453595, 0.004352831649535879, 0.01353565372035049,
    0.01724424051296911, 0.009033534817205653, -0.011389864418482169, -0.03474597495886764, -0.044312495004405754,
    -0.023875138464235692, 0.03224034924002493, 0.11300543605954934, 0.19292638019851646, 0.24262366023074244,
    0.24262366023074247, 0.19292638019851646, 0.11300543605954934, 0.03224034924002493, -0.0238751384642357,
    -0.04431249500440576, -0.034745974958867644, -0.01138986441848217, 0.009033534817205653, 0.01724424051296911,
    0.013535653720350498, 0.0043528316495358805, -0.0033318393261453595, -0.006055013116446954, -0.004477466799346431,
    -0.0013501901565744485, 0.0009770267293160938, 0.0017376237448470022, 0.0013628123002057632, 0.0004984330412411764};

static void conv(int16_t const *const x, size_t offset, int16_t *y)
{
    int32_t accum = 0;

    for (size_t i = 0; i < 40; i++)
    {
        const size_t j = offset - (20 - i - 1);
        accum += taps[i] * (j >= 0 ? x[j] : 0);
    }

    *y = accum;
}

int main(int argc, char *argv[])
{
    lpc_filter_t *f = lpc_filter_new();
    assert(f);

    lpc_seq_decoder_t *dec = lpc_seq_decoder_new();
    assert(dec);

    for (size_t i = 0; i < LPC_MAX_SEQ; i++)
    {
        lpc_seq_t const *s[1] = {lpc_get_seq(i)};
        size_t all = 4 * lpc_seq_decoder_update(dec, (const lpc_seq_t *const *)&s, 1);

        {
            bool finished = false;
            size_t samples = 0;
            fix16_t y;
            int16_t buf_tmp[all];
            int16_t buf_out[all];

            while (!finished)
            {
                uint32_t rnd = rand();
                finished = lpc_seq_decoder_exec(dec, rnd, &y);
                int64_t v = (int64_t)y * INT16_MAX / (2 * FIX_ONE);
                // interpolate
                buf_tmp[samples++] = v;
                buf_tmp[samples++] = 0;
                buf_tmp[samples++] = 0;
                buf_tmp[samples++] = 0;
            }

            for (size_t j = 0; j < samples; j++)
            {
                conv(buf_tmp, j, &buf_out[j]);
            }

            size_t written = fwrite(buf_out, 2, all, stdout);
            assert(written == all);
            fflush(stdout);
        }
    }

    exit(EXIT_SUCCESS);
}
