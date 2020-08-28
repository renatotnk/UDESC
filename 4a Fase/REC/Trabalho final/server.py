#!/usr/bin/env python2
# -*- coding: utf-8 -*

from TCP import *

servidor = TCP()

servidor.server('localhost', 45000)
