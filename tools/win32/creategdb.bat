@ECHO off

ECHO > insight.ini
ECHO file %1 >> insight.ini
ECHO target remote 127.0.0.1:55555 >> insight.ini
ECHO load %1 >> insight.ini
ECHO b main >> insight.ini
ECHO c >> insight.ini
