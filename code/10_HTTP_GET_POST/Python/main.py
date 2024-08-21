import requests  
  
url = 'https://yapi.pro/mock/194105/emp/list'  
response = requests.get(url)  
print(response.status_code)  # 打印响应状态码  
print(response.text)         # 打印响应内容（字符串形式）
 
url = 'https://yapi.pro/mock/194105/postData'  
data = {'code': '12'}  
response = requests.post(url, data=data)  
print(response.json())  # 如果响应是JSON格式，则可以直接解析