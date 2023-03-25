## 見守り当番 Observer v1.0.1
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

解説記事-->"[【高齢化社会】M5Stickで高齢者の見守り装置を作った。[見守り当番]](https://qiita.com/nih/items/a832ae7ad478fdb6e4ab)"

# Operation
- M5ボタン - 計測時間をリセットします。押すと「reset」と表示されます。配置後に押すことを想定しています。
- サイドボタン - デバッグモードのオンオフを入れ替えできます。デバックモードがオフの時、表示が「.」固定になり、その逆はドアが開いているか閉まっているかを画面に表示します。配置時の動作確認時に使用することを想定しています。

# Attention
- M5StickCでは書き込み時にGND接続を外して下さい。
- M5Stickは、M5StackとLEDの電圧設定が逆です。

# Version History
- v1.0.0 - 23/3/15 release
- v1.0.1 - 23/3/20 define JA name