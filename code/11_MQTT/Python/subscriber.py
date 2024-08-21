# subscriber.py
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    # 订阅，需要放在 on_connect 里
    # 如果与 broker 失去连接后重连，仍然会继续订阅 raspberry/topic 主题
    client.subscribe("raspberry/topic")

# 回调函数，当收到消息时，触发该函数
def on_message(client, userdata, msg):
    print(f"{msg.topic} {msg.payload}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# 设置遗嘱消息，当树莓派断电，或者网络出现异常中断时，发送遗嘱消息给其他客户端
client.will_set('raspberry/status',  b'{"status": "Off"}')

# 创建连接，三个参数分别为 broker 地址，broker 端口号，保活时间
client.connect("broker.emqx.io", 1883, 60)

# 设置网络循环堵塞，在调用 disconnect() 或程序崩溃前，不会主动结束程序
client.loop_forever()
