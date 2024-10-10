#!/bin/bash
proc prm.pc
gcc -g -I $ORACLE_HOME/precomp/public -L $ORACLE_HOME/lib -lclntsh -lrt -lpthread reactor.c common.c shmmap.c prm.c run.c -o d1 2>&1 | grep error