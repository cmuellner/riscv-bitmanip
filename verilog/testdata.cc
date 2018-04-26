#include <stdio.h>
#include "../cproofs/common.h"
using namespace rv32b;

int main()
{
	FILE *f;

	f = fopen("testdata_grev.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t shamt = xorshift32() & 31;
		uint32_t dout = grev32(din, shamt);
		fprintf(f, "%08x%02x%08x\n", din, shamt, dout);
	}
	fclose(f);

	f = fopen("testdata_gzip.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t mode = xorshift32() & 31;
		while (1) {
			bool mode_inv = mode & 1;
			uint32_t mode_upper = mode >> 1;
			if (pcnt(mode_upper) == 1 && mode_inv) {
				mode = xorshift32() & 31;
				continue;
			}
			if (clz(mode_upper) + pcnt(mode_upper) + ctz(mode_upper) != 32) {
				mode = xorshift32() & 31;
				continue;
			}
			break;
		}
		uint32_t dout = gzip32(din, mode);
		fprintf(f, "%08x%02x%08x\n", din, mode, dout);
	}
	fclose(f);

	f = fopen("testdata_bfxp.hex", "w");
	for (int i = 0; i < 1000; i++) {
		uint32_t din = xorshift32();
		uint32_t start = xorshift32() & 31;
		uint32_t len = xorshift32() & 31;
		uint32_t dest = xorshift32() & 31;
		uint32_t dout = bfxp(din, start, len, dest);
		fprintf(f, "%08x%02x%02x%02x%08x\n", din, start, len, dest, dout);
	}
	fclose(f);

	return 0;
}