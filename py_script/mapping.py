
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import json
import sys

#コマンドライン引数受取
args = sys.argv
config_name = args[1]
print("config file name:", config_name)

#jsonファイル読み込み
json_open = open(config_name,'r')
json_load = json.load(json_open)

#データ読み込み
road_csv = json_load["mapCsv"]
som_csv  = json_load["somCsv"]
result_csv = config_name[12:]
result_csv = result_csv[:-5]

road_df = pd.read_csv(road_csv,header=None)
som_df  = pd.read_csv(som_csv)
result_df = pd.read_csv("output_csv/" + result_csv + ".csv")

# 2. マップデータの準備
# ---------------------------------------------------------
# 道路地図をNumPy配列に変換
road_map = road_df.values
height, width = road_map.shape

# リスクマップを初期化（地図と同じサイズの0埋め配列）
risk_map = np.zeros((height, width))

# リスクデータを埋める
# risk1, risk2, risk3 の合計をそのセルのリスクとして扱います
for index, row in som_df.iterrows():
    h, w = int(row['map_h']), int(row['map_w'])

    # 座標が地図の範囲内かチェック
    if 0 <= h < height and 0 <= w < width:
        total_risk = row['risk1'] + row['risk2'] + row['risk3']
        risk_map[h, w] = total_risk

# 3. 可視化
# ---------------------------------------------------------
plt.figure(figsize=(10, 8))

# A. 背景：道路地図を描画 (グレースケール)
plt.imshow(road_map, cmap='gray_r', alpha=0.3, label='Road')
# gray_r: 白黒反転（道路が見やすいように調整）

# B. 重ね合わせ：リスクマップを描画 (ヒートマップ)
# リスクが0の場所は透明にするためにマスク処理を行います
masked_risk = np.ma.masked_where(risk_map == 0, risk_map)
plt.imshow(masked_risk, cmap='jet', alpha=0.6, interpolation='nearest')
plt.colorbar(label='Total Risk Level')

# C. 経路：アントの移動軌跡をプロット
# matplotlibでは plot(x, y) なので plot(w, h) の順に渡します
plt.plot(result_df['x'], result_df['y'], color='darkviolet', linewidth=2, label='Individual Path', alpha=0.8)

# スタートとゴールの強調
start_h, start_w = result_df.iloc[0]['y'], result_df.iloc[0]['x']
goal_h, goal_w = result_df.iloc[-1]['y'], result_df.iloc[-1]['x']

plt.scatter(start_w, start_h, color='blue', s=150, label='Start', edgecolors='white', zorder=10)
plt.scatter(goal_w, goal_h, color='red', marker='*', s=200, label='Goal', edgecolors='white', zorder=10)

# グラフの装飾
plt.title("Genetic Algorithm path with Risk Overlay")
plt.xlabel("Width (w)")
plt.ylabel("Height (h)")
plt.legend(loc='upper right')
plt.grid(False) # 画像の上にグリッド線は不要なためOFF

# 表示
plt.tight_layout()
plt.show()