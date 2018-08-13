#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int fun()
{
	printf("hello");
	return 1;
}

int main(int argc,char *argv[])
{
	FILE *sf,*df;

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	char new_file_name[_MAX_EXT];

		//参数检查
	if(argc == 1)
	{
		printf("请直接把文件拖到本程序\n\n\n");
		system("PAUSE");
		return 0;
	}
	_splitpath(argv[1],drive,dir,fname,ext);
	sprintf(new_file_name,"%s%s%s.h",drive,dir,fname);


	sf = fopen(argv[1],"r");
	if(sf == NULL)
	{
		printf("open file %s error\n",argv[1]);
		system("PAUSE");
		return 0;
	}

	df = fopen(new_file_name,"w");
	if(df == NULL)
	{
		fclose(sf);
		printf("open file %s error\n",new_file_name);
		system("PAUSE");
		return 0;
	}

	{
		double num;
		char   add_space = 0;
		//跳过特殊文件头
		fseek(sf,4,SEEK_SET);
		fputs("#ifndef __ARRAY_15_9_H\n",df);
		fputs("#define __ARRAY_15_9_H\n",df);
		fputs("float array9[]=\n{\n",df);

		//开始读入数据
		while(!feof(sf))
		{
			fscanf(sf,"%le",&num);
			fprintf(df,"%1.9f,",num);
			if(add_space++ == 4)
			{
				add_space = 0;
				fputc('\n',df);
			}
		}
		fseek(df,-1,SEEK_END);
		fputs("\n};\n",df);

		//跳过特殊文件头
		add_space = 0;
		fseek(sf,4,SEEK_SET);
		fputs("\ndouble array15[]=\n{\n",df);

		//开始读入数据
		while(!feof(sf))
		{
			fscanf(sf,"%le",&num);
			fprintf(df,"%1.15f,",num);
			if(add_space++ == 4)
			{
				add_space = 0;
				fputc('\n',df);
			}
		}
		fseek(df,-1,SEEK_END);
		fputs("\n};\n",df);
		fputs("#endif //__ARRAY_15_9_H\n",df);
	}

	fclose(df);
	fclose(sf);
	return 0;
}