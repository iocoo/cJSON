#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_tools.h"

#define BUFLEN 12288

int parse(char *str);

int main()
{

    printf("Json Parse Starting...!\n");
    //zzIconvInit();
    FILE *fp;
    char buff[BUFLEN];
    memset(buff,'\0',sizeof(buff));
    if((fp=fopen("json.txt","rb"))==NULL)
    {
     printf("CAN NOT OPEN THIS FILE!\n");
     exit(1);
    }

    if(!fread(buff,sizeof(char),BUFLEN,fp))
    {
        printf("Read file Fail\n");
        exit(1);
    }

    printf("%s",buff);
    parse(buff);

    fclose(fp);


    return 0;
}

int parse(char *str)
{

    int i;
    char retCode[8];
    char listInvoiceInfoNew[12280];
	char outlistInvoiceInfoNew[12280];
	memset(retCode,0,sizeof(retCode));
	memset(listInvoiceInfoNew,0,sizeof(listInvoiceInfoNew));
    memset(outlistInvoiceInfoNew,0,sizeof(outlistInvoiceInfoNew));
    char *in_list[]={"m_strFeeName", "m_strTotalCnt", "m_strCellCount","m_strTotalFee", "m_strBillId","m_strItemType", "m_nItemLevel",  "m_strUnit",

	"m_strBillBeginDate", "m_strBillEndDate", "m_llUsableBalance","m_llOtherBalance","m_llCurUnpayAmt", "m_llCurTotalFee", "m_strExt1", "m_strExt2"};

	char strlistLen[4];
	int listLen=0;
	memset(strlistLen,0,sizeof(strlistLen));

	if(get_JsonValue(str,"Code",retCode,J_STRING))
        printf("Return Success\n");

	if(!strcmp("0000",retCode))

	{

		get_JsonValue(str,"listInvoiceInfoNew",listInvoiceInfoNew,J_ARRAY); //array
		printf("%s\n",listInvoiceInfoNew);
		for(i=0;*(listInvoiceInfoNew+i)!='|';i++);

		strncpy(strlistLen,listInvoiceInfoNew,i);

		listLen=atoi(strlistLen);

		if(listLen==0)

   			strcpy(outlistInvoiceInfoNew,"0;");

   		else

			get_JsonArrayValue(listInvoiceInfoNew,in_list,16,outlistInvoiceInfoNew);

       printf(";%d;%s",listLen,outlistInvoiceInfoNew);
	 }
	 return 0;
}
