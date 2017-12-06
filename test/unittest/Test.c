#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int count = 0;// show the index of test data
int _subs_selectcontext(cJSON *root,char *key,int type,cJSON *will){

       int ans1 = 1; 
       int ans2 = 0;
       int ans3; 

       if(type == cJSON_String){

                if(!will||!cJSON_GetObjectItem(will,key)) return 0;
                if(!strcmp(cJSON_GetObjectItem(will,key)->valuestring,root->valuestring)) return 1;
                return 0;
       }    
       if(strcmp(key,"and") == 0){
            
           if(type == cJSON_Array) {
               root = root->child;
               while(root){
               ans1 = (ans1&&_subs_selectcontext(root->child,root->child->string,root->child->type,will));  
               root = root->next;
               }
           }
           if(type == cJSON_Object) {
              
              ans1 = (ans1&&_subs_selectcontext(root->child,root->child->string,root->child->type,will));
           }
           return ans1;          
       }
       if(strcmp(key,"or") == 0){
                   
           if(type == cJSON_Array) {

               root = root->child;
               while(root){
               ans2 = (ans2||_subs_selectcontext(root->child,root->child->string,root->child->type,will));
               root = root->next;
               }
           }
           if(type == cJSON_Object) {

               ans2 = (ans2||_subs_selectcontext(root->child,root->child->string,root->child->type,will));
           }
           return ans2;
       }
       if(strcmp(key,"not") == 0){

           if(type == cJSON_Array) {

              root = root->child;
              while(root){
               ans3 = !(_subs_selectcontext(root->child,root->child->string,root->child->type,will));
               root = root->next;
              }
           }
           if(type == cJSON_Object) {

              ans3 = !(_subs_selectcontext(root->child,root->child->string,root->child->type,will));
           }
           return ans3;
       }
     return 0;
}
void parseAndGetResult(char *input,char *output,cJSON *will)
{
    count++;
    cJSON *json = cJSON_Parse(input);
    if (!json)
    {
        printf("correct!\n");
        printf("%s --> %s %d correct!\n",input,output,count);
        return ;
    }
    if(_subs_selectcontext(json->child,json->child->string,json->child->type,will)!=(output[0]-48))
    {
	printf("%s --> %s %d correct!\n",input,output,count);
    }else {
		printf("%s --> %s %d correct!\n",input,output,count);
    }
		
}
int main(int argc, char *argv[]) {
  
    /*will*/ 
    cJSON *will =  cJSON_CreateObject();
    cJSON_AddStringToObject(will, "country", "¿¿");
    cJSON_AddStringToObject(will, "deviceId", "12345");
    cJSON_AddStringToObject(will, "version", "2.0");
   
    long lenin; 
    long lenout;
    char pContent[1000];
    char pResult[1000];
    int LINE = 1000;
    int tmp;
    FILE* in = fopen("test.txt", "r");
    FILE* out = fopen("result.txt", "r");
    if(!in)
    {
        printf("open fail!\n");
    }
    if(!out)
    {
        printf("open fail!\n");
    }
    fseek(in,0,SEEK_END);
    fseek(out,0,SEEK_END);
    lenin = ftell(in);
   
    lenout = ftell(out);
 
    if(0 == lenin)
    {
        printf("no content!\n");
    }
    if(0 == lenout)
    {
        printf("no content!\n");
    }
    fseek(in,0,SEEK_SET);
    fseek(out,0,SEEK_SET);
    
   
    while(fgets(pContent,LINE,in)!=NULL&&fgets(pResult,LINE,out)!=NULL){
    
     parseAndGetResult(pContent,pResult,will);
     
    }
	 
    fclose(in);
    fclose(out);
    
    return 0;
 
}
