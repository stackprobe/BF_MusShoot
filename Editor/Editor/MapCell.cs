using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
	public class MapCell
	{
		public TileImage Tile;
		public int MapIndex;
		public int XPos;
		public int YPos;

		public MapCell(TileImage ti, int mapIndex, int xPos, int yPos)
		{
			this.Tile = ti;
			this.MapIndex = mapIndex;
			this.XPos = xPos;
			this.YPos = yPos;
		}
	}
}
