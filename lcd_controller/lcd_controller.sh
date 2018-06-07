#!/bin/bash
#message=`redis-cli blpop message 0 | sed -n 2p | xargs`
mode=`redis-cli get button`
if [ "$mode" == "0" ]; then
  temperature=`redis-cli get temperature`
  light=`redis-cli get humidity`

  last_message=`redis-cli get message`
  message="${temperature} celsius      ${light} humidity"

  # reduce blink
  if [ "$message" != "$last_message" ]; then
    ./lcd_controller "$message"
    redis-cli set message "${message}" > /dev/null
  fi
elif [ "$mode" == "1" ]; then
  token_balance=`redis-cli get token_balance`
  ./lcd_controller "wish $token_balance Token to change?"
elif [ "$mode" == "2" ]; then
  token_balance=`redis-cli get token_balance`
  change=`python -c "print int(${token_balance} * 0.001)"`
  redis-cli incrby account $change
  redis-cli set button 3
  redis-cli expire button 4
elif [ "$mode" == "3" ]; then
  token_balance=`redis-cli get token_balance`
  account=`redis-cli get account`
  ./lcd_controller "acc: $account / token: $token_balance"
else
  redis-cli set button 0
fi
