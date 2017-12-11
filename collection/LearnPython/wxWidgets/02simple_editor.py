import wx

class MainFrame(wx.Frame):
    def __init__(self, parent, id, title, size):
        wx.Frame.__init__(self, parent, id=id, title=title, size=size)
        self.text_ctrl = wx.TextCtrl(self, id=wx.ID_ANY, style=wx.TE_MULTILINE)
        self.CreateStatusBar()

        file_menu = wx.Menu()
        file_menu.Append(wx.ID_NEW, "&New File", "New A File")
        file_menu.AppendSeparator()
        file_menu.Append(wx.ID_SAVE, "&Save", "Save File")
        file_menu.Append(wx.ID_EXIT, "&Exit")

        about_menu = wx.Menu()
        about_menu.Append(wx.ID_ABORT, "&About")

        menu_bar = wx.MenuBar()
        menu_bar.Append(file_menu, "&File")
        menu_bar.Append(about_menu, "&?")

        self.SetMenuBar(menu_bar)

        self.Bind(wx.EVT_MENU, self.OnExit, id=wx.ID_EXIT)
        self.Bind(wx.EVT_MENU, self.OnAbout, id=wx.ID_ABORT)

    def OnAbout(self, evt):
        dialog = wx.MessageDialog(self, "A small text editor", "About Sample Editor", wx.OK)
        dialog.ShowModal()

    def OnExit(self, evt):
        self.Destroy()


class MyApp(wx.App):
    def __init__(self):
        wx.App.__init__(self)
        main_frame = MainFrame(None, wx.ID_ANY, "Simple Editor", wx.Size(600, 600))
        main_frame.CenterOnScreen(wx.BOTH)
        main_frame.Show()

app = MyApp()
app.MainLoop()