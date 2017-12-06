#!/usr/bin/env python
# Test whether a client subscibe to a topic  can recieve correct message by wrong filter
import subprocess

import inspect, os, sys
# From http://stackoverflow.com/questions/279237/python-import-a-module-from-a-folder
cmd_subfolder = os.path.realpath(os.path.abspath(os.path.join(os.path.split(inspect.getfile( inspect.currentframe() ))[0],"..")))
if cmd_subfolder not in sys.path:
    sys.path.insert(0, cmd_subfolder)

import mosq_test
import json

rc = 1
mid = 53
keepalive = 60
data = {
       'realWill' : 'sorry',
       'willLength' : '5',
       'country' : 'USA'
       }
payload = json.dumps(data)
connect_packet = mosq_test.gen_connect("sub-wrongfiter-will", keepalive=keepalive,will_topic="wrongfilter/test",will_payload=payload)
connack_packet = mosq_test.gen_connack(rc=0)

subscribe_packet = mosq_test.gen_subscribe(mid, "wrongfilter/test", 0)
suback_packet = mosq_test.gen_suback(mid, 0)
publish_packet = mosq_test.gen_publish("wrongfilter/test", qos=0, payload='')

cmd = ['../../src/mosquitto', '-p', '1888']
broker = mosq_test.start_broker(filename=os.path.basename(__file__), cmd=cmd)

try:
    sock = mosq_test.do_client_connect(connect_packet, connack_packet, timeout=30)
    sock.send(subscribe_packet)

    if mosq_test.expect_packet(sock, "suback", suback_packet):
        will = subprocess.Popen(['./11-pub-wrongfilter-will.py'])
        will.wait()

        if mosq_test.expect_packet(sock, "publish", publish_packet) == 0:
            rc = 0

    sock.close()
finally:
    broker.terminate()
    broker.wait()
    if rc:
        (stdo, stde) = broker.communicate()
        print(stde)

exit(rc)

