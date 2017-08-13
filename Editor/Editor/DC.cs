using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.IO;

namespace Editor
{
	public class DC
	{
		public static DC I = new DC();

		private DC()
		{ }

		public TileImage DefaultTile;
		public List<MapTable> MapTableList = new List<MapTable>();
		public ResourceDataList EnemyCommonParamPromptList;
		public List<Enemy> EnemyList = new List<Enemy>();
		public FieldTable FieldMap;

		public void Init()
		{
			this.DefaultTile = new TileImage(
				new ImageFile(Consts.RESOURCE_DIR + "\\normal\\empty.bmp"),
				new ImageFile(Consts.RESOURCE_DIR + "\\selected\\empty.bmp")
				);

			BusyWin.SetMessage("背景オブジェクトを読み込んでいます...");

			{
				string[] niDirs = Directory.GetDirectories(Consts.RESOURCE_DIR + "\\normal\\map");
				string[] siDirs = Directory.GetDirectories(Consts.RESOURCE_DIR + "\\selected\\map");

				for (int index = 0; index < niDirs.Length; index++)
				{
					string niDir = niDirs[index];
					string siDir = siDirs[index];

					this.MapTableList.Add(new MapTable(niDir, siDir, index));
				}

				// Check ...

				if (this.MapTableList.Count < Consts.MAPTABLE_NUM_MIN)
				{
					throw new Exception("マップテーブルが少なすぎます。");
				}
			}

			BusyWin.SetMessage("敵オブジェクトを読み込んでいます...");

			{
				ResourceData reader = new ResourceData(Consts.DATA_DIR + "\\Enemy.txt");

				DC.I.EnemyCommonParamPromptList = reader.ReadBlock();

				string[] files = Directory.GetFiles(Consts.RESOURCE_DIR + "\\enemy");
				string[] niFiles = Directory.GetFiles(Consts.RESOURCE_DIR + "\\normal\\enemy");
				string[] siFiles = Directory.GetFiles(Consts.RESOURCE_DIR + "\\selected\\enemy");

				for (int index = 0; ; index++)
				{
					string name = reader.ReadValue();

					if (name == ResourceData.DEFAULT_VALUE)
						break;

					this.EnemyList.Add(new Enemy(
						new ImageFile(files[index]),
						new TileImage(
							new ImageFile(niFiles[index]),
							new ImageFile(siFiles[index])
							),
						name,
						reader.ReadBlock()
						));
				}
			}

			BusyWin.SetMessage("フィールドマップを読み込んでいます...");

			{
				ResourceData backTable = new ResourceData(Consts.DATA_DIR + "\\WallData.txt");
				ResourceData frontTable = new ResourceData(Consts.DATA_DIR + "\\StageData.txt");

				DC.I.FieldMap = new FieldTable(backTable, frontTable);
			}

			BusyWin.SetMessage("初期化を続行しています...");

			{
				ResourceData reader = new ResourceData(Consts.DATA_DIR + "\\Settings.txt");

				DC.I.FieldScrollMax = Tools.ParseInt(reader.ReadValue(), -1, Consts.FIELDMAP_W_MIN, Consts.FIELDMAP_W_MAX);
			}
		}

		public int MapTableIndex = 0;
		public int FieldSheetLeftXPos = 0;
		public int FieldScrollMax = Consts.FIELDMAP_W_MIN;
		public bool DispBackLayer = true;
		public bool DispFrontLayer = true;
		public bool LeftClickDeHaichi = false;
		public bool NoDispGridLine = false;

		public void SaveData()
		{
			List<string> backText = new List<string>();
			List<string> frontText = new List<string>();

			for (int x = 0; x < DC.I.FieldMap.Width; x++)
			{
				for (int y = 0; y < Consts.FIELDMAP_H; y++)
				{
					FieldCell fc = this.FieldMap.Table[x][y];

					FieldCellData.AddToText(backText, fc.BackCD);
					FieldCellData.AddToText(frontText, fc.FrontCD);
				}
			}
			Tools.RTrim(backText);
			Tools.RTrim(frontText);

			File.WriteAllLines(Consts.DATA_DIR + "\\WallData.txt", backText.ToArray(), Tools.CP932);
			File.WriteAllLines(Consts.DATA_DIR + "\\StageData.txt", frontText.ToArray(), Tools.CP932);
		}

		public FieldCell[][] CopiedTable;
		public int CT_W;
		public int CT_H;
	}
}
