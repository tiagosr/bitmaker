#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import pyximport; pyximport.install()
import nes

class BitmakerMemoryBlock:
    def __init__(self, size, auto_expand=False):
        self.b = bytearray(size)
    def ensureSize(self, size):
        if len(self.b) < size:
            old_b = self.b
            self.b = bytearray(size)
            self.b[0:len(old_b)] = old_b

class Packed8bpp8x8Tile:
    "SNES (Mode 7) and GBA graphics"
    def __init__(self, mem, offset):
        self.mem = mem
        self.offset = offset
        self.mem.ensureSize(offset+64)
    def setPixel(self, x, y, value):
        value = int(value) & 255
        x = int(x) & 7
        y = int(y) & 7
        self.mem.b[self.offset + y*8 + x] = value
    def copyFrom(self, other):
        for b in range(0, 63):
            self.mem[self.offset + b] = other.mem[other.offset + b]
        
class Packed4bpp8x8Tile:
    "Mega Drive graphics"
    def __init__(self, mem, offset):
        self.mem = mem
        self.offset = offset
        self.mem.ensureSize(offset+32)
    def setPixel(self, x, y, value):
        value = int(value) & 15
        x = int(x) & 7
        y = int(y) & 7
        b = self.mem.b[self.offset + y*4 + (x >> 1)]
        if x & 1:
            b = b & 0xf0 + value
        else:
            b = b & 0x0f + value << 4
        self.mem.b[self.offset + y*4 + (x >> 1)] = b
    def copyFrom(self, other):
        for b in range(0, 31):
            self.mem[self.offset + b] = other.mem[other.offset + b]

class Planar4bpp8x8TileLSB:
    "SNES and Master System"
    def __init__(self, mem, mem_offset):
        self.mem = mem
        self.offset = offset
        self.mem.ensureSize(offset+32)
    def setPixel(self, x, y, value):
        value = int(value) & 15
        x = 7-(int(x) & 7)
        y = int(y) & 7
        for bx in [0, 1, 2, 3]:
            b = self.mem.b[self.offset + y*4 + bx]
            self.mem.b[self.offset + y*4 + bx] = b & ~(1<<x) | ((1<<x) if value & (1<<bx) else 0)
    def copyFrom(self, other):
        for b in range(0, 31):
            self.mem[self.offset + b] = other.mem[other.offset + b]

class Planar2bpp8x8TileLSB:
    "SNES and NES"
    def __init__(self, mem, mem_offset):
        self.mem = mem
        self.offset = offset
        self.mem.ensureSize(offset+16)
    def setPixel(self, x, y, value):
        value = int(value) & 3
        x = 7-(int(x) & 7)
        y = int(y) & 7
        for bx in [0, 1]:
            b = self.mem[self.offset + y*2 + bx]
            self.mem[self.offset + y*2 + bx] = b & ~(1<<x) | ((1<<x) if value & (1<<bx) else 0)
    def copyFrom(self, other):
        for b in range(0, 15):
            self.mem[self.offset + b] = other.mem[other.offset + b]


class BitmakerPaletteItem(QGraphicsItem):
    def __init__(self):
        super(BitmakerPaletteItem, self).__init__()

class BitmakerPaletteWidget(QGraphicsScene):
    pass

class BitmakerScene(QTreeWidgetItem):
    def __init__(self):
        super().__init__(QTreeWidgetItem.Type)
        self.objects = {}
        self.setName("New Scene")
    def setName(self, new_name):
        self.name = new_name
        self.setText(new_name)
class BitmakerLibrary(QTreeWidgetItem):
    def __init__(self):
        super().__init__(QTreeWidgetItem.Type)
        self.objects = {}
        self.setName("Library")
    def setName(self, new_name):
        self.name = new_name
        self.setText(new_name)

class BitmakerRasterizerPreview(QPixmap):
    def __init__(self, width, height):
        super(BitmakerRasterizer, self).__init__(QSize(width, height))
        self.width = width
        self.height = height
    def makeScreen(self):
        pass

class BitmakerScene(QGraphicsItem):
    def __init__(self):
        super(BitmakerScene, self).__init__()
    def paint(self, painter, option, widget):
        pass
class BitmakerSceneView(QWidget):
    def __init__(self):
        super().__init__()
        self.scene = QGraphicsScene(self)
        self.view = QGraphicsView(self.scene, self)
        self.show()    


class BitmakerProjectModel(QStandardItemModel):
    def __init__(self):
        super().__init__()
        self.scenes = QTreeWidgetItem(QTreeWidgetItem.Type)
        self.scenes.setText("Scenes")
        self.libraries = QTreeWidgetItem(QTreeWidgetItem.Type)
        self.libraries.setText("Libraries")
        self.appendRow(self.scenes)
        self.appendRow(self.libraries)
    def addNewScene(self):
        scene = BitmakerScene()
        self.scenes.addChild(scene)
    def addNewLibrary(self):
        lib = BitmakerLibrary()
        self.libraries.addChild(lib)
class BitmakerProjectWindow(QDockWidget):
    def __init__(self):
        super().__init__()
        self.setup()
    def setup(self):
        self.projectTree = QTreeView()
        self.setWidget(self.projectTree)
        self.setFloating(false)
class BitmakerMainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.actions = {}
        self.menus = {}
        self.initSetup()
    def initSetup(self):
        self.statusBar().showMessage('Ready.')
        self.setWindowTitle('Bitmaker')
        self.menuSetup()
        #self.
        self.show()
    def menuSetup(self):
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')
        fileMenu.addAction(self.menuSetupAction('New Project', '&New project...', 'Ctrl+N', 'new.png', 'Create a new project', self.menuNewProject))
        fileMenu.addAction(self.menuSetupAction('Open Project', '&Open project...', 'Ctrl+O', 'open.png', 'Open an existing project', self.menuOpenProject))
        fileMenu.addAction(self.menuSetupAction('Save Project', '&Save project', 'Ctrl+S', 'save.png', 'Save the current project', self.menuSaveProject))
        fileMenu.addAction(self.menuSetupAction('Save Project As', '&Save project as...', None, None, 'Save the current project with a file name', self.menuSaveProjectAs))
        fileMenu.addSeparator()
        fileMenu.addAction(self.menuSetupAction('Preferences', 'Preferences', 'Ctrl+,', None, 'Browse and set configuration parameters', None))
        fileMenu.addSeparator()
        fileMenu.addAction(self.menuSetupAction('Exit Bitmaker', 'Exit Bitmaker', 'Ctrl+Q', None, 'Exit Bitmaker', self.menuQuit))
        self.menus['File'] = fileMenu
        editMenu = menubar.addMenu('&Edit')
        editMenu.addAction(self.menuSetupAction('Undo', 'Undo last action', 'Ctrl+Z', 'undo.png', 'Undo last executed action', None))
        editMenu.addAction(self.menuSetupAction('Redo', 'Redo last undone action', 'Ctrl+Shift+Z', 'redo.png', 'Redo last undone action', None))
        editMenu.addAction(self.menuSetupAction('Repeat', 'Repeat last action', 'Ctrl+Y', 'repeat.png', 'Repeat last executed action', None))
        editMenu.addSeparator()
        editMenu.addAction(self.menuSetupAction('Cut', 'Cut', 'Ctrl+X', 'cut.png', 'Cut current selection', None))
        editMenu.addAction(self.menuSetupAction('Copy', 'Copy', 'Ctrl+C', 'copy.png', 'Copy current selection', None))
        editMenu.addAction(self.menuSetupAction('Paste', 'Paste', 'Ctrl+V', 'paste.png', 'Paste item(s) from clipboard', None))
        editMenu.addSeparator()
        self.menus['Edit'] = editMenu
        windowMenu = menubar.addMenu('&Window')
        self.menus['Window'] = windowMenu
        helpMenu = menubar.addMenu('&Help')
        helpMenu.addAction(self.menuSetupAction('Documentation', 'Documentation', None, None, 'Browse documentation', None))
        self.menus['Help'] = helpMenu
    # menu actions
    def menuSetupAction(self, name, menu_caption, shortcut, icon, status_tip, trigger):
        if icon:
            action = QAction(QIcon(icon), menu_caption, self)
        else:
            action = QAction(menu_caption, self)
        if shortcut:
            action.setShortcut(shortcut)
        action.setStatusTip(status_tip)
        if trigger:
            action.triggered.connect(trigger)
        self.actions[name] = action
        return action
    # menu signals
    @pyqtSlot()
    def menuNewProject(self):
        print("TODO: new project")
    @pyqtSlot()
    def menuOpenProject(self):
        print("TODO: open project")
    @pyqtSlot()
    def menuSaveProject(self):
        self.saveProject()
    @pyqtSlot()
    def menuSaveProjectAs(self):
        print("TODO: save project as")
    @pyqtSlot()
    def menuPreferences(self):
        print("TODO: open preferences")
    @pyqtSlot()
    def menuQuit(self):
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Question)
        msg.setStandardButtons(QMessageBox.Save | QMessageBox.Close | QMessageBox.Cancel)
        msg.setText("Do you want to save the project before closing Bitmaker?")
        msg.setWindowTitle("Closing Bitmaker")
        res = msg.exec_()
        if res == QMessageBox.Save:
            self.saveProject()
            qApp.quit()
        if res == QMessageBox.Close:
            qApp.quit()
    # application-wise stuff
    def saveProject(self):
        print("TODO: save project")
    

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setApplicationName('Bitmaker')
    w = BitmakerMainWindow()
    #app.exec_()
    sys.exit(app.exec_())
