from ctypes import *
dll = windll.LoadLibrary(".\\UqLib.dll")

str = 'テスト'
enc_str = str.encode('shift-jis')
dll.UqLibInit(enc_str)

str = 'test.png'
enc_str = str.encode('shift-jis')
bmp1 = dll.CreateTextureFromFile(enc_str)

while True:
  bool1 = dll.UpdateWindowMessage()
  if bool1 == -1:
    break
  
  bool2 = dll.BeginDrawing()
  if bool2 == -1:
    break

  dll.DrawTexture(0, 0, bmp1)
  dll.EndDrawing();

dll.UqLibEnd();
