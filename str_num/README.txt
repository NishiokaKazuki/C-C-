C++
文字列 数値相互変換

strconv.hをincludeすることでクラス使用可能
符号付整数、符号無整数、浮動小数点型に対応(関数の詳細はcppに明記)

エラー発生時はクラス変数であるsi_Errchkが変化
-1 なら失敗、1 なら成功

また現在はDEBUGモードでstrconv.hにあるSTRCONV_DEBUGを
コメント化することで無効。