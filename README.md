my english is untrustful.even though i dont know if there is a word "untrustful".
i write this for myself,if somebody else can not get the point,not my fault.


i want to push  messages to my devices,then choose mosquitto as the broker.
but it is not so "geili" or good.all the subscribers of a same topic will receive the message which was published to the topic,that's not cool.

so i modify the source code,want to filtering the message.some devices will receive,some won't.of course,they all subscribed to the topic.

i notice that mosquitto push the message according to a tree named "subscribe tree".so i add some code to do filter while the tree is traversed.

the code is on src/subs.c,i add a function named "_subs_selectcontext".

to make the filter function come true,i put the filters to payload,so i have to parse the payload,divide the filter and message.the message will stored by mosquitto while the filter will used by me in the function "_subs_selectcontext".

so how to do with it?when we connect to the broker,we must send something to the broker,and the broker must store it,so we can use those value to make the filter function work.i use the value "will",which use for suddenly disconnect in mosquitto.set a will topic and the set the will contain device data when the connect is build.of course you can add something to the client struct,and use it to do this thing,not will.

when i get filter and will,the thing is simple, only the clients in the subscribe tree those pass the filter will join to the queue,others not.

the will will parsed to "realWill" and data.the payload will parsed to "realMessage" and "filter",the subscribes will only see realMessage.of course,there can be no will and no filter,if there is no filter,the function will not be invoke.i'm not so noob.

the compare is not so simple.i use json and use logic word "or" and "and" and "not" to make the filter.for example,the payload is {"realMessage":"you're beaultiful","filter":"{"and":[{ "or":[{ "country":"USA"},{ "country":"JPA"}]},{"and":[{"not":{"version":"1.0"}},{"not":{"version":"2.0"}},{"not":{"version":"1.0"}}]}]}"}

and one client who subscribe to this topic with will {"realWill":"i am die","country":"JPA","version":"2.0","clour":"yellow"} will not receive the message.because it's version is 2.0,it's country is CN,so this logical statement's value is false.if the version is 3.0,then things will diffierent.

I put the unitest code to the tese/unitest/,code covers nothing,can see more example there.
use the project by follow steps.
git clone this repository.
make 
meet errors
fix errors
install

 







 




