import wx

app = wx.App()
main_frame = wx.Frame(None, title="Hello World!", id=wx.ID_ANY)
main_frame.Show()
app.MainLoop()