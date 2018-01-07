import pythoncom
import pyHook

def OnMouseEvent(event):
    if event.Message != pyHook.HookConstants.WM_LBUTTONDOWN:
        return True

    print 'MessageName: ', event.MessageName
    print 'MessageID: ', event.Message
    print 'Time: ', event.Time
    print 'Position: ', event.Position
    print '================================'
    return True


def OnKeyboardEvent(event):
    print 'MessageName: ', event.MessageName
    print 'MessageID: ', event.Message
    print 'Time: ', event.Time
    print 'KeyID: ', event.KeyID
    print 'Ascii: ', event.Ascii, chr(event.Ascii)
    print 'Key: ', event.Key
    print '================================'
    return True

hook_manager = pyHook.HookManager()
# hook_manager.MouseLeftUp = OnMouseLeftUpEvent
hook_manager.MouseAll = OnMouseEvent
hook_manager.KeyAll = OnKeyboardEvent

hook_manager.HookMouse()
hook_manager.HookKeyboard()

pythoncom.PumpMessages()

























