#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from PyQt5 import QtCore
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QAction, QMainWindow, QApplication, qApp, QWidget


class BitmakerApplication(QApplication):
    pass

class BitmakerMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initSetup()
    def initSetup(self):
        self.statusBar().showMessage('Ready.')
        self.setWindowTitle('Bitmaker')
        self.menuSetup()
        self.show()
    def menuSetup(self):
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')
        fileMenu.addAction(self.menuSetupExit())
    
    def menuSetupExit(self):
        exitAction = QAction(QIcon('exit.png'), '&Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit Bitmaker')
        exitAction.triggered.connect(qApp.quit)
        return exitAction

    

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = BitmakerMainWindow()
    app.exec_()
    #sys.exit(app.exec_())
