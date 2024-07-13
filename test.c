#include <stdio.h>
#include <stdlib.h>
#include "cdk.h"
#include "rs.h"

#define DATA_SHARDS      10
#define PARITY_SHARDS    3
#define BLOCK_SIZE       256

int main()
{
	FILE*            infile;
	FILE*            outfile;
	size_t           file_size;
	reed_solomon*    rs;
	size_t           nrShards;
	size_t           nrBlocks;
	size_t           i;
	size_t           nrFecBlocks;
	char*            data;
	size_t           n;
	char**           data_blocks;
	char*            marks;
	size_t           corrupted;

	cdk_logger_init(NULL, false);
	reed_solomon_init();

	infile = cdk_fopen("input.txt", "rb");
	if (!infile) {
		cdk_loge("open input.txt faild.\n");
		abort();
	}
	rs       = reed_solomon_new(DATA_SHARDS, PARITY_SHARDS);
	nrShards = rs->shards;

	fseek(infile, 0, SEEK_END);
	file_size = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	nrBlocks = (file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;
	nrBlocks = ((nrBlocks + DATA_SHARDS - 1) / DATA_SHARDS) * DATA_SHARDS;
	

	i           = nrBlocks / DATA_SHARDS;
	nrFecBlocks = i * PARITY_SHARDS;
	nrShards    = nrBlocks + nrFecBlocks;

	cdk_logd("file_size: %d, nrShards: %d, nrBlocks: %d\n", file_size, nrShards, nrBlocks);

	data = malloc(nrShards * BLOCK_SIZE);
	if (!data) {
		cdk_loge("malloc failed.\n");
		fclose(infile);
		abort();
	}
	n = fread(data, 1, file_size, infile);
	if (n < file_size) {
	
		cdk_loge("read file failed.\n");
		fclose(infile);
		abort();
	}
	fclose(infile);

	memset(data + file_size, 0, nrShards * BLOCK_SIZE - file_size);

	data_blocks = (unsigned char**)malloc(nrShards * sizeof(unsigned char**));
	for (i = 0; i < nrShards; i++) {
		data_blocks[i] = data + i * BLOCK_SIZE;
	}

	reed_solomon_encode(rs, data_blocks, (int)(nrBlocks + nrFecBlocks), BLOCK_SIZE);

	marks = calloc(1, nrShards);
	memset(marks, 0, sizeof(marks));
	corrupted = PARITY_SHARDS;
	for (i = 0; i < corrupted; i++) {
		size_t corr = cdk_rand(0, (int)nrBlocks);
		memset(data + BLOCK_SIZE * corr, 137, BLOCK_SIZE);
		marks[corr] = 1;
		cdk_logd("corrupted block: %zu\n", corr);
	}

	reed_solomon_reconstruct(rs, data_blocks, marks, (int)nrShards, BLOCK_SIZE);

	outfile = cdk_fopen("output.txt", "wb+");
	if (!outfile) {
		cdk_loge("open output.txt faild.\n");
		abort();
	}
	fwrite(data, 1, file_size, outfile);
	fclose(outfile);

	free(data);
	free(data_blocks);
	free(marks);
	reed_solomon_release(rs);
	return 0;
}