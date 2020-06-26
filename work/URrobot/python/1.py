import numpy as np
import socket
import time
import struct
# import util
# import rtde

HOST = "192.168.232.129"
PORT = 30003


def movel(target_tcp):
    tool_acc = 1.2  # Safe: 0.5
    tool_vel = 0.25  # Safe: 0.2
    tool_pos_tolerance = [0.001, 0.001, 0.001, 0.05, 0.05, 0.05]
    tcp_command = "movel(p[%f,%f,%f,%f,%f,%f],a=%f,v=%f,t=3,r=0)\n" % (
        target_tcp[0], target_tcp[1], target_tcp[2], target_tcp[3], target_tcp[4],
        target_tcp[5],
        tool_acc, tool_vel)
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.connect((HOST, PORT))
    tcp_socket.send(str.encode(tcp_command))  # 利用字符串的encode方法编码成bytes，默认为utf-8类型
    tcp_socket.close()
movel([0, -0.47, 0.13, 3.14165, 0., 0.])
time.sleep(3)
movel([0, -0.27, 0.13, 3.14165, 0., 0.])

# def move_to_tcp(target_tcp):
#     tool_acc = 1.2  # Safe: 0.5
#     tool_vel = 0.25  # Safe: 0.2
#     tool_pos_tolerance = [0.001, 0.001, 0.001, 0.05, 0.05, 0.05]
#     tcp_command = "movel(p[%f,%f,%f,%f,%f,%f],a=%f,v=%f,t=0,r=0)\n" % (
#         target_tcp[0], target_tcp[1], target_tcp[2], target_tcp[3], target_tcp[4],
#         target_tcp[5],
#         tool_acc, tool_vel)
#     tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#     tcp_socket.connect((HOST, PORT))
#     tcp_socket.send(str.encode(tcp_command))  # 利用字符串的encode方法编码成bytes，默认为utf-8类型
#     tcp_socket.close()
# move_to_tcp([0, -0.47, 0.13, 3.14165, 0., 0.])


  
