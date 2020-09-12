using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class Consts
	{
		public const string DATA_DIR = "..\\..\\..\\..\\EditorData";
		public const string RESOURCE_DIR = "C:\\appdata\\BF_MusShootTileData";

		public const int MAPTABLE_NUM_MIN = 3; // 1-
		public const int MAPTABLE_W_MIN = 3; // 1-
		public const int MAPTABLE_H_MIN = 3; // 1-

		public const int TILE_W = 16;
		public const int TILE_H = 16;

		public const int FIELDMAP_W_MIN = 100;
		public const int FIELDMAP_W_MAX = 10000;
		public const int FIELDMAP_H = 30;

		public const int FIELDSHEET_W = 100;
		public const int FIELDSHEET_H = Consts.FIELDMAP_H;

		public const int ENEMY_INDEX_OF_WALL = 0;
	}
}
