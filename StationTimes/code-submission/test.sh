#!/bin/bash

# Trigger all your test cases with this script
cat mytests/nextday1.in | xargs -a mytests/nextday1.args ./timetable
cat mytests/badline.in | xargs -a mytests/badline.args ./timetable
cat mytests/toobig.in | xargs -a mytests/toobig.args ./timetable
cat mytests/notimetable.in | xargs -a mytests/notimetable.args ./timetable
