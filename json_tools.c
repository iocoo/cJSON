
#include "json_tools.h"
#include "convch.h"

//pthread_mutex_t call_curl_Mutex = PTHREAD_MUTEX_INITIALIZER;

char sBusiParams[]="\"BusiParams\":{\"sPrivData\":{\"m_iOpId\": \"15\",\"m_iOpEntityId\":\"3\",\"m_iOrgId\": \"5\",\"m_iVestOrgId\": \"2\"}"  ;	//ҵ�� �û�Ȩ����

char strCcsOpId[]="\"strCcsOpId\": \"10086\"";		//�������

char sClientId[]="ClientId:com.cmcc.sh.outer.ivr";


//����Jsonʹ��cJson

int get_JsonValue(const char *Res_string,const char * key,char *pValue,int type)

{

	//memset(out,0,16);

	int number;

	int flag=0;

	//memset(pValue,'\0',sizeof(pValue));

	strcpy(pValue,"");

	cJSON* pItem = NULL;

	cJSON* pArrayItem = NULL;

	int i,nCount=0;

	cJSON* pRoot = cJSON_Parse ( Res_string );

   	 while ( pRoot )

   	{



        do

        {

            pItem = cJSON_GetObjectItem ( pRoot, key);

           if(pItem){ //printf("a!");

            switch(type)

            {

            	case 0:					//�ַ���

            		strcpy(pValue,pItem->valuestring);

					flag=1;

            		break;

            	case 1:					//��������

            		sprintf(pValue,"%d",pItem->valueint);

					flag=1;

            		break;

            	case 2:				//����long long

            		sprintf(pValue,"%lld",pItem->valuellong);

					flag=1;

            		break;

            	case 3:				//

            		sprintf(pValue,"%lf",pItem->valuedouble);

					flag=1;

                     break;

                case 4: //array

                    nCount = cJSON_GetArraySize( pItem); //��ȡpArray����Ĵ�С,�����ַ���Ԫ�أ�

                  	sprintf(pValue,"%d|",nCount);

                    sprintf(pValue,"%s%s",pValue,cJSON_PrintUnformatted( pItem ));

                    if(pArrayItem!=NULL)

                    	cJSON_Delete(pArrayItem);

					flag=1;

                     break;

                 case 5: //object

                 	sprintf(pValue,"%s",cJSON_PrintUnformatted( pItem ));

                     flag=1;

                     break;

            	default:

            		break;

        	}

         }

            if(pRoot->next)

               pRoot=pRoot->next;

            else break;

        }while(!pItem&&pRoot);

		if(pRoot->child)

        	pRoot=pRoot->child;

        else break;

    }

    if(pRoot!=NULL)

   	 cJSON_Delete (pRoot);

    return flag;

}



char * get_JsonArrayValue(char *in, char **find_char, int inLen,char *out)

{

	/************************************************************************/

	// in�������ַ���

	// find_char[] Ŀ�괮��Ϊһϵ�д��� inLenΪ�䳤��

	// out ������;Ϊ�ָ�����ֵ��˳��Ϊfind_char��Ӧ˳��

	//

	/***********************************************************************/

   int k, i=0,j=0;

   char buff[12];

   char tmbuff[12880];

   memset(tmbuff,'\0',sizeof(tmbuff));

   sprintf(out,"");

   char *p;

   char *p1;

   int len=0;

   if(*in=='0'||strlen(in)==0)		//��������СΪ0����ʱֱ�ӷ���;

   {

       sprintf(out,"0;");

       return out;

   }



   for(i=0;*(in+i)!='|';i++);

   strncpy(buff,in,i);

   len=atoi(buff);

   if(*(++in)=='|'&&*(++in)=='['&&*(++in)!='{')

    {

        strncpy(out,in,strlen(in)-1);	//��[]��������;

        //sprintf(out,"%s%s",out,";");

        strcat(out,";");

        return out;

    }





    for(i=0;i<len;i++)

    {

        for(j=0;j<inLen;j++)

        {

        	memset(tmbuff,'\0',sizeof(tmbuff));		//����

            p = strstr(in,find_char[j]);

            p = strstr(p,":");

            p1 = p+1;

            for(k = 0;k < 256;k++)

            {

                p++;

                //in++;

                if(*p==','||*p=='}')

                break;

            }

            strncpy(tmbuff, p1, p-p1);

            sprintf(out,"%s%s",out,tmbuff);//20120608

            if(j<inLen-1)

            	strcat(out,"|");
        }

       in++;
       in=strstr(in,"};");

       printf("\n%s\n",in);

       strcat(out,",");//20120608

     }

   return out;



}



char * get_JsonObjectValue(char *in,char *find_char[],int inLen,char *out)

{

   int k, i=0,j=0;

   char buff[12];

   char tmbuff[512];

   memset(buff,'\0',sizeof(buff));

   memset(tmbuff,'\0',sizeof(tmbuff));

   char *p;

   char *p1;

   if(*in!='{'||strlen(in)==0)

   {

       sprintf(out," ");

       return out;

   }



    for(j=0;j<inLen;j++)

    {

        memset(tmbuff,'\0',sizeof(tmbuff));

        p = strstr(in,find_char[j]);

        p = strstr(p,":");

        p1 = p+1;

        for(k = 0;k < 32;k++)

        {

            p++;

            if(*p==','||*p=='}')

            break;

        }

        strncpy(tmbuff, p1, p-p1);

        sprintf(out,"%s%s;",out,tmbuff);

    }

   return out;
}



