#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


class BitmakerApplication(QApplication):
    pass

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

class BitmakerRasterizer(QPixmap):
    def __init__(self, width, height):
        super(BitmakerRasterizer, self).__init__()
    def paint(self, painter, option, widget):
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
