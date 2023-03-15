# Observer v1.0
一定時間ドアの開閉が行われなかった時、LINEに通知します。
高齢者の見守り装置としての使用を想定しています。

# What you need
- M5StickC Plus
- 磁気ドアセンサー x1
- LINENotifyのToken x1
- WiFi環境

# How to use
[Observer.ino](https://github.com/11104/Observer/blob/main/Observer/Observer.ino)のプログラム9~12行目にWiFi情報とLINENotifyTokenを入れてM5Stickに書き込んでください。
13行目は通知するまでの時間間隔です。デフォルトでは12時間になっています。
26番ピンとGNDピンに磁気ドアスイッチを差し込み、ドアに設置します。
電源を入れると「.」とだけ表示されます。

解説記事-->"[【高齢化社会】M5Stickで高齢者の見守り装置を作った。[Observer]](https://qiita.com/nih/items/a832ae7ad478fdb6e4ab)"

# Attention
- M5StickCでは書き込み時にGND接続を外して下さい。
- M5Stickは、M5StackとLEDの電圧設定が逆です。