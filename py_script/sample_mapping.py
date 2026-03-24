import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 1. ファイルパスの直接指定
# 実行環境に合わせて、実際のファイルパスに書き換えてください
roadCsvPath = "input_csv/shizuoka_cropped_road.csv"
somCsvPath = "input_csv/shizuoka_cropped_sample_som.csv"
resultCsvPath = "output_csv/best_route.csv"

# 2. データの読み込み
roadDf = pd.read_csv(roadCsvPath, header=None)
somDf = pd.read_csv(somCsvPath)
resultDf = pd.read_csv(resultCsvPath)

# 3. マップデータの準備
roadMap = roadDf.values
mapHeight, mapWidth = roadMap.shape

# リスクマップを初期化（地図と同じサイズの0埋め配列）
riskMap = np.zeros((mapHeight, mapWidth))

# リスクデータを埋める
for index, row in somDf.iterrows():
    h = int(row['map_h'])
    w = int(row['map_w'])

    # 座標が地図の範囲内かチェック
    if 0 <= h < mapHeight and 0 <= w < mapWidth:
        totalRisk = row['risk1'] + row['risk2'] + row['risk3']
        riskMap[h, w] = totalRisk

# 4. 可視化
plt.figure(figsize=(10, 8))

# A. 背景：道路地図を描画 (グレースケール)
plt.imshow(roadMap, cmap='gray_r', alpha=0.3, label='Road')

# B. 重ね合わせ：リスクマップを描画 (ヒートマップ)
# リスクが0の場所は透明にするためにマスク処理を行います
maskedRisk = np.ma.masked_where(riskMap == 0, riskMap)
plt.imshow(maskedRisk, cmap='jet', alpha=0.6, interpolation='nearest')
plt.colorbar(label='Total Risk Level')

# C. 経路：個体の移動軌跡をプロット
# resultDfには step, x, y の列が含まれている前提
plt.plot(resultDf['x'], resultDf['y'], color='darkviolet', linewidth=2, label='Individual Path', alpha=0.8)

# スタートとゴールの強調
startW = resultDf.iloc[0]['x']
startH = resultDf.iloc[0]['y']
goalW = resultDf.iloc[-1]['x']
goalH = resultDf.iloc[-1]['y']

plt.scatter(startW, startH, color='blue', s=150, label='Start', edgecolors='white', zorder=10)
plt.scatter(goalW, goalH, color='red', marker='*', s=200, label='Goal', edgecolors='white', zorder=10)

# グラフの装飾
plt.title("Genetic Algorithm Path with Risk Overlay")
plt.xlabel("Width (x)")
plt.ylabel("Height (y)")
plt.legend(loc='upper right')
plt.grid(False)

# 表示
plt.tight_layout()
plt.show()