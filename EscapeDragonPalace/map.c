#include "init.h"
#include "map.h"

// CMD ����
typedef enum CMDColor
{
	E_Black,
	E_Blue,
	E_Green,
	E_Teal, // û�ϻ�
	E_Red,
	E_Purple,
	E_Yellow,
	E_White,
	E_Gray,
	E_BrightBlue,
	E_BrightGreen,
	E_BrightTeal,
	E_BrightRed,
	E_BrightPurple,
	E_BrightYellow,
	E_BrightWhite,
} CMDColor;

typedef enum MapBgColor
{
	E_CJail = E_Gray,
	E_CDragonPalace = E_BrightBlue,
	E_CSea1 = E_Blue,
	E_CSea2 = E_Blue,
	E_CGround = E_Green,
} MapBgColor;

typedef enum MapStatus
{
	E_Jail,
	E_DragonPalace,
	E_Sea1,
	E_Sea2,
	E_Ground,
} MapStatus;

typedef struct StageBG
{
	MyPoint pos;
	CMDColor color;
	char bg[20][256];
} StageBG;

int g_Plus = 0;
int g_Key;
char g_Map[49][80] =
{
	"��==========================================================================��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��============================================                              ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                              ============================================��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��============================================                              ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��                                                                          ��",
	"��==========================================================================��",
};

// ��� ���
StageBG g_StageBG[STAGE_CNT][BG_CNT] =
{
{ // �� - ����
	{
		{2, 1},
		E_Gray,
		{
			"�� ��������������������������������������",
			"�� ��������������������������������������",
			"�� ��������������������������������������",
			"�� ��������������������������������������",
			"�� ��������������������������������������",
			"�� ��       ����������������������������",
			"�� ��       ����������������������������",
			"�� ��       ����������������������������",
			"�� ��       ����������������������������",
			"�� ��       ����������������������������",
			"�� ��       ����������������������������",
		},
	},
	{
		{6, 7},
		E_BrightBlue,
		{
			"  @@@",
			" @@ @@",
			"@@ @ @@",
			" @@ @@",
			"  @@@",
		} // Goal
	},
},
{ // �� - ���
	{
		{36, 4},
		E_Gray,
		{
			"                 /\\        /\\",
			"                ( (________) )",
			"               /             \\",
			"       _______/               \\_______",
			"       \\                             /",
			"        \\___________________________/",
			"             |       ___       |",
			"   __________|______|_|_|______|________",
			"   \\                                   /",
			"    \\_________________________________/",
			"         |        _________        |",
			"         |       |    |    |       |",
			"   ______|_______|____|____|_______|____",
			"  /",
			" /",
			"/_______________________________________",
			"     |           ___________          |",
			"     |          |     |     |         |",
			"     |          |    .|.    |         |",
			"     |          |     |     |         |",
		},
	},
	{
		{3, 29},
		E_Gray,
		{
			"         __ ",
			"       / / /",
			"       \\ \\ \\    __ ",
			"       / / /  / / /",
			"  __   \\ \\ \\  \\ \\ \\",
			"/ / /  / / /  / / /",
			"\\ \\ \\  \\ \\ \\  \\ \\ \\",
		}
	},
	{
		{45, 42},
		E_Gray,
		{
			"        __",
			"       \\ \\ \\",
			" __    / / /",
			"\\ \\ \\  \\ \\ \\",
			"/ / /  / / /",
			"\\ \\ \\  \\ \\ \\",
		}
	},
	{
		{3, 38},
		E_Gray,
		{
			"_____________________ ",
			"                     \\ ",
			"                      \\ ",
			"                       \\ ",
			"________________________\\ ",
			"                  |",
			"_________         |",
			"   |     \\        |",
			"  .|.    |        |",
			"   |     |        |",
		}
	},
	{
		{4, 7},
		E_BrightBlue,
		{
			"  @@@",
			" @@ @@",
			"@@ @ @@",
			" @@ @@",
			"  @@@",
		} // Goal
	},
},
};

StageBG g_StagePlatform[STAGE_CNT][BG_CNT] =
{
{
	{
		{4, 4},
		E_BrightWhite,
		{
			"======",
		}
	},

},
};

MapStatus g_MapStatus = E_DragonPalace;

// �� �׸���
void DrawMap()
{
	// �� Ʋ �׸���
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		_DrawText(0, y, g_Map[y + g_Plus]);
	}

	// ��� �׸���
	for (int i = 0; i < STAGE_CNT; i++)
	{
		StageBG* tmpBG = g_StageBG[g_MapStatus]; // ���� ���� ��� ���� ��������
		int printCnt = MAP_HEIGHT;
		for (int j = MAP_HEIGHT; j >= 0; j--)
		{
			int tmpY = tmpBG[i].pos.y + j - g_Plus;
			if (tmpY < 0 || tmpY > MAP_HEIGHT) // ����� ���� ����� �� ��� X
				continue;
			_DrawTextColor(tmpBG[i].pos.x, tmpY, tmpBG[i].bg[j], tmpBG[i].color);
		}
	}
}

// �� ��ġ ������Ʈ
void UpdateMapPos()
{
	if (g_Key == 'w' || g_Key == 'W')
	{
		--g_Plus;
	}
	else if (g_Key == 's' || g_Key == 'S')
	{
		++g_Plus;
	}
	if (g_Plus < 0)
		g_Plus = 0;
	else if (g_Plus > 24)
		g_Plus = 24;
}