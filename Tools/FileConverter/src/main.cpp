//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
// 
// EncodeXOR 関数については、以下を参考にしました。
// https://blogoftrueone.wordpress.com/2013/06/15/%E3%83%AA%E3%82%BD%E3%83%BC%E3%82%B9%E3%82%92%E8%AA%AD%E3%81%BF%E8%BE%BC%E3%82%80%EF%BC%88%E3%81%9D%E3%81%AE%EF%BC%91%EF%BC%89/
//-----------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

char* EncodeXOR(char* data)
{
	for(int i=0; i < 256; i++)
	{
		// データがなければ抜ける
		if( data[i] == 0 )
		{
			break;
		}
		data[i] = 0x99;
	}
	return data;
}

int main(int argc, char* argv[]){
	if (argc != 2)
	{
		std::cout << argc;
		return 0;
	}
	FILE *fp;
	fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);
	char *buffer = (char*)malloc(sizeof(char)*size);
	size_t result = fread(buffer, 1, size, fp);
	
	string aaa = regex_replace(argv[1], regex(".png"), ".dat");
	
	FILE *tmpf = fopen(aaa.c_str(), "wb");
	fwrite(EncodeXOR(buffer), 1, size, tmpf);
	fflush(tmpf);
	fclose(tmpf);
	return 0;
}
