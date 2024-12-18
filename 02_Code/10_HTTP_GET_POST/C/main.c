#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <curl/curl.h>  

//用于处理接收到的数据的回调函数
size_t GetDataWriteCallback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    //将读到的数据放进标准输出打印出来
    //fwrite(ptr, size, nmemb, stdout); 
    char *str = (char*)ptr; 
    printf("%s\n",str);
    return size * nmemb; // 返回写入的字节数 
}

int GetUrlData(const char *url)
{
    CURL *curl;  
    CURLcode res;  
  
    curl = curl_easy_init();
    if(curl)
    {
        // 设置要访问的URL  
        curl_easy_setopt(curl, CURLOPT_URL, url);  
        // 禁用将HTTP头输出到标准输出（如果你需要的话，可以开启这个选项）  
        curl_easy_setopt(curl, CURLOPT_HEADER, 0L);  
        // 设置数据接收的回调函数  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GetDataWriteCallback);  
        // 执行CURL会话  
        res = curl_easy_perform(curl);  
        // 检查是否有错误发生  
        if (res != CURLE_OK) {  
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));  
            return 1;  
        }      
        // 清理  
        curl_easy_cleanup(curl);  
        return 0; 
    }
    return 1;
}

size_t PostDataWriteCallback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    //将读到的数据放进标准输出打印出来
    //fwrite(ptr, size, nmemb, stdout); 
    char *str = (char*)ptr; 
    printf("%s\n",str);
    return size * nmemb; // 返回写入的字节数 
}

int PostUrlData(const char *url, const char *json_data)
{
    CURL *curl;  
    CURLcode res;  
  
    curl = curl_easy_init();  
    if (curl) {  
        // 设置要访问的URL  
        curl_easy_setopt(curl, CURLOPT_URL, url);  
        // 设置POST请求  
        curl_easy_setopt(curl, CURLOPT_POST, 1L);  
        // 设置POST数据  
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);  
        // 设置Content-Type头  
        struct curl_slist *headers = NULL;  
        headers = curl_slist_append(headers, "Content-Type: application/json");  
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);  
        // 设置数据接收的回调函数（对于POST请求，这通常不是必需的）  
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, PostDataWriteCallback);  
        // 执行CURL会话  
        res = curl_easy_perform(curl);  
        // 检查是否有错误发生  
        if (res != CURLE_OK) {  
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));  
            curl_slist_free_all(headers); // 释放HTTP头  
            curl_easy_cleanup(curl);  
            return 1;  
        }  
        // 释放HTTP头  
        curl_slist_free_all(headers);  
  
        // 清理  
        curl_easy_cleanup(curl);  
        return 0;  
    }  
  
    // 如果curl初始化失败  
    return 1;  
}

int main(int argc,char **argv)
{
    curl_global_init(CURL_GLOBAL_ALL);

    const char *GetUrl = "https://yapi.pro/mock/194105/emp/list"; 
    if (!GetUrlData(GetUrl)) {  
        printf("Data fetched successfully.\n");  
    } else {  
        printf("Failed to fetch data.\n");  
    } 

    const char *PostUrl = "https://yapi.pro/mock/194105/postData";
    const char *json_data = "{\"code\":\"13\"}"; // 示例JSON字符串
    if (!PostUrlData(PostUrl,json_data)) {  
        printf("JSON data posted successfully.\n");  
    } else {  
        printf("Failed to post JSON data.\n");  
    } 

    curl_global_cleanup(); 
    return 0; 
}