#!/usr/bin/env python

# publish a message with filter to a topic.

# The client should connect to port 1888 with keepalive=60, clean session set,

import inspect
import os
import socket
import sys
import json

# From http://stackoverflow.com/questions/279237/python-import-a-module-from-a-folder
cmd_subfolder = os.path.realpath(os.path.abspath(os.path.join(os.path.split(inspect.getfile( inspect.currentframe() ))[0],"..")))
if cmd_subfolder not in sys.path:
    sys.path.insert(0, cmd_subfolder)

import mosq_test
rc = 1
keepalive = 60
connect_packet = mosq_test.gen_connect("pub-filter-wrongwill", keepalive=keepalive)
connack_packet = mosq_test.gen_connack(rc=0)
data = {
      'filter' :{ 'or':[{ 'country':'USAa'},{ 'country':'JPA'}]},
      'realMessage' : 'helloworld',
      'messageLen' : 10
  }
load = json.dumps(data)
publish_packet = mosq_test.gen_publish("filter/wrongwill", qos=0, payload = load)


sock = mosq_test.do_client_connect(connect_packet,connack_packet)
rc = 0
sock.send(publish_packet)
sock.close();


exit(rc)



