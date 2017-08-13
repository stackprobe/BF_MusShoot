using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class Enemy
	{
		public ImageFile Mitame;
		public TileImage Tile;
		public string Name;
		public ResourceDataList ParamPromptList;

		public Enemy(ImageFile mitame, TileImage ti, string name, ResourceDataList ppl)
		{
			this.Mitame = mitame;
			this.Tile = ti;
			this.Name = name;
			this.ParamPromptList = ppl;
		}
	}
}
