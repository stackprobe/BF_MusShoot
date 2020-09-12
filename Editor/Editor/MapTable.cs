using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Editor
{
	public class MapTable
	{
		public List<List<MapCell>> Table = new List<List<MapCell>>(); // [y][x]

		public MapTable(string niRtDir, string siRtDir, int mapIndex)
		{
			string[] niDirs = Directory.GetDirectories(niRtDir);
			string[] siDirs = Directory.GetDirectories(siRtDir);

			Array.Sort(niDirs, string.Compare);
			Array.Sort(siDirs, string.Compare);

			for (int index = 0; index < niDirs.Length; index++)
			{
				string niDir = niDirs[index];
				string siDir = siDirs[index];

				string[] niFiles = Directory.GetFiles(niDir);
				string[] siFiles = Directory.GetFiles(siDir);

				Array.Sort(niFiles, string.Compare);
				Array.Sort(siFiles, string.Compare);

				this.Table.Add(new List<MapCell>());

				for (int subndx = 0; subndx < niFiles.Length; subndx++)
				{
					string niFile = niFiles[subndx];
					string siFile = siFiles[subndx];

					this.Table[this.Table.Count - 1].Add(new MapCell(
						new TileImage(
							new ImageFile(niFile),
							new ImageFile(siFile)
							),
						mapIndex,
						subndx,
						index
						));
				}
			}

			// Check ...

			if (this.Width < Consts.MAPTABLE_W_MIN || this.Height < Consts.MAPTABLE_H_MIN)
			{
				throw new Exception("マップテーブルが小さすぎます。");
			}
			for (int y = 1; y < this.Height; y++)
			{
				if (this.Table[0].Count != this.Table[y].Count)
				{
					throw new Exception("マップテーブルの幅が均一ではありません。[ " + y + " ] 行目を確認して下さい。");
				}
			}
		}

		public int Width
		{
			get
			{
				return this.Table[0].Count;
			}
		}
		public int Height
		{
			get
			{
				return this.Table.Count;
			}
		}

		public void Touch()
		{
			for (int y = 0; y < this.Height; y++)
			{
				BusyWin.SetMessage("マップ読み込み中... " + y + " / " + this.Height);

				for (int x = 0; x < this.Width; x++)
				{
					TileImage tile = this.Table[y][x].Tile;

					if (tile.NormalImage.ImageData == null) { } // touch
					if (tile.SelectedImage.ImageData == null) { } // touch
				}
			}
		}
	}
}
