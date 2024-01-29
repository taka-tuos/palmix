#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <omp.h>

struct pal_t {
	const char *name;
	int no;
	int power;
	int idx;
};

struct pal_t pal_list[] = {
	{ "モコロン", 1, 1470, 27 },
	{ "ツッパニャン", 2, 1460, 46 },
	{ "タマコッコ", 3, 1500, 62 },
	{ "クルリス", 4, 1430, 7 },
	{ "キツネビ", 5, 1400, 20 },
	{ "カモノスケ", 6, 1330, 59 },
	{ "ボルトラ", 7, 1410, 65 },
	{ "エテッパ", 8, 1250, 107 },
	{ "ヒノコジカ", 9, 1155, 138 },
	{ "ペンタマ", 10, 1350, 23 },
	{ "キャプペン", 11, 520, 122 },
	{ "パチグリ", 12, 1370, 17 },
	{ "コチグリ", 12, 1360, 18 },
	{ "ナエモチ", 13, 1240, 112 },
	{ "ナエモチ(特殊)", 13, 1240, 113 },
	{ "タマモ", 14, 1450, 79 },
	{ "ホウロック", 15, 1390, 82 },
	{ "チョロゾウ", 16, 1490, 14 },
	{ "ンダコアラ", 17, 1380, 47 },
	{ "ミルフィー", 18, 1455, 135 },
	{ "ネムラム", 19, 1230, 106 },
	{ "イノボウ", 20, 1130, 6 },
	{ "ルナティ", 21, 1180, 121 },
	{ "モグルン", 22, 1220, 101 },
	{ "ヤミイカ", 23, 1290, 85 },
	{ "ニャオテト", 24, 1480, 4 },
	{ "チルテト", 24, 1440, 5 },
	{ "ルミカイト", 25, 870, 128 },
	{ "ガウルフ", 26, 1060, 15 },
	{ "クルットリ", 27, 1340, 8 },
	{ "ポプリーナ", 28, 1280, 91 },
	{ "ミルカルビ", 29, 910, 86 },
	{ "イバラヒメ", 30, 1320, 21 },
	{ "シャーキッド", 31, 1090, 25 },
	{ "シャーマンダー", 31, 1100, 26 },
	{ "シメナワ", 32, 1420, 31 },
	{ "オバケナワ", 32, 1422, 32 },
	{ "ササゾー", 33, 430, 97 },
	{ "ライゾー", 33, 390, 98 },
	{ "メリポップ", 34, 1190, 39 },
	{ "ベリゴート", 35, 930, 75 },
	{ "メルパカ", 36, 890, 41 },
	{ "ツノガミ", 37, 920, 9 },
	{ "ヤマガミ", 37, 900, 10 },
	{ "ホークウィン", 38, 420, 90 },
	{ "ヒメウサ", 39, 1310, 117 },
	{ "ヘルゴート", 40, 590, 2 },
	{ "アビスゴート", 40, 580, 3 },
	{ "パピテフ", 41, 490, 132 },
	{ "ブルフェルノ", 42, 790, 99 },
	{ "トドドドン", 43, 895, 136 },
	{ "マスクロウ", 44, 1080, 44 },
	{ "ダリザード", 45, 1120, 57 },
	{ "チリザード", 45, 1140, 58 },
	{ "ツキカゲ", 46, 950, 30 },
	{ "エアムルグ", 47, 1030, 12 },
	{ "フェザーロ", 48, 1020, 52 },
	{ "サンドロ", 48, 1000, 53 },
	{ "ゴリレイジ", 49, 1040, 16 },
	{ "ビーナイト", 50, 1070, 95 },
	{ "クインビーナ", 51, 330, 94 },
	{ "ニャンギマリ", 52, 510, 131 },
	{ "コモップ", 53, 1300, 114 },
	{ "ドンモップ", 54, 410, 115 },
	{ "オコチョ", 55, 800, 123 },
	{ "ライコーン", 56, 680, 19 },
	{ "フブキツネ", 57, 760, 104 },
	{ "サラブレイズ", 58, 360, 35 },
	{ "サラブラック", 58, 240, 36 },
	{ "ツララジカ", 59, 880, 76 },
	{ "イヌズマ", 60, 740, 100 },
	{ "シラヌイ", 61, 830, 56 },
	{ "カミナラシ", 62, 1210, 24 },
	{ "ミステリア", 63, 1110, 22 },
	{ "アロアリュー", 64, 820, 63 },
	{ "ビリビリュー", 64, 810, 64 },
	{ "シーペント", 65, 560, 42 },
	{ "スナペント", 65, 550, 43 },
	{ "ソルレイス", 66, 1150, 51 },
	{ "ドリタス", 67, 850, 11 },
	{ "ニャンバット", 68, 750, 96 },
	{ "ラブマンダー", 69, 940, 81 },
	{ "ラヴィ", 70, 1405, 137 },
	{ "カバネドリ", 71, 660, 60 },
	{ "シロカバネ", 71, 620, 61 },
	{ "ツジギリ", 72, 640, 127 },
	{ "ライバード", 73, 220, 118 },
	{ "イグニクス", 74, 380, 126 },
	{ "クレメーオ", 75, 700, 116 },
	{ "フォレーナ", 76, 1160, 80 },
	{ "ラベロット", 77, 990, 103 },
	{ "ヴィオレッタ", 78, 1050, 89 },
	{ "シルキーヌ", 79, 450, 78 },
	{ "シルフィア", 80, 540, 37 },
	{ "シルティア", 80, 530, 38 },
	{ "ケルピス", 81, 1260, 83 },
	{ "マグピス", 81, 1270, 84 },
	{ "アズレーン", 82, 500, 45 },
	{ "ツンドラー", 83, 130, 40 },
	{ "ゴクエンオ", 84, 710, 108 },
	{ "シンエンオ", 84, 670, 109 },
	{ "ペコドン", 85, 280, 54 },
	{ "パリピドン", 85, 270, 55 },
	{ "ラブラドン", 86, 860, 71 },
	{ "スプラドン", 86, 840, 72 },
	{ "フラリーナ", 87, 780, 130 },
	{ "ボルカノン", 88, 320, 49 },
	{ "フロスカノン", 88, 230, 50 },
	{ "アルパオー", 89, 470, 110 },
	{ "アオパオー", 89, 440, 111 },
	{ "グランモス", 90, 300, 68 },
	{ "ブリザモス", 90, 290, 69 },
	{ "ヒエティ", 91, 460, 87 },
	{ "トロピティ", 91, 480, 88 },
	{ "グラクレス", 92, 340, 119 },
	{ "ムラクモ", 93, 980, 48 },
	{ "ヤミトバリ", 94, 1010, 70 },
	{ "フェスキー", 95, 350, 124 },
	{ "ボルカイザー", 96, 10, 74 },
	{ "ヘルガルダ", 97, 190, 125 },
	{ "ジオラーヴァ", 98, 150, 102 },
	{ "デスティング", 99, 260, 133 },
	{ "アヌビス", 100, 570, 1 },
	{ "レヴィドラ", 101, 310, 28 },
	{ "アグニドラ", 101, 315, 29 },
	{ "スザク", 102, 50, 33 },
	{ "シヴァ", 102, 30, 34 },
	{ "エレパンダ", 103, 200, 13 },
	{ "リリクイン", 104, 250, 92 },
	{ "ルナクイン", 104, 210, 93 },
	{ "ホルス", 105, 370, 73 },
	{ "ボルゼクス", 106, 140, 134 },
	{ "ゼノグリフ", 107, 60, 77 },
	{ "セイントール", 108, 80, 120 },
	{ "ベイントール", 109, 70, 129 },
	{ "グレイシャル", 110, 120, 66 },
	{ "グレイシャドウ", 110, 100, 67 },
	{ "ジェットラン", 111, 90, 105 },
};

// r,p1,p2
int uniq_bleed[] = {
	55,54,65,
	3,2,51,
	5,4,23,
	61,60,104,
	10,9,31,
	38,37,42,
	36,35,116,
	69,68,87,
	98,97,13,
	64,63,100,
	18,17,23,
	67,66,125,
	111,110,76,
	93,92,133,
	58,57,137,
	109,108,70,
	53,52,101,
	72,71,59,
	43,42,136,
	26,25,138,
	34,33,28,
	50,49,104,
	32,31,114,
	92,97,130,
	73,60,1,
	13,97,100,
	134,13,54,
	77,56,102
};

int bleed_table[1501] = { 0 };

void create_table() {
	for(int p = 0; p < 1501; p++) {
		int dif = 3000;
		int idx = 9999;
		int iid = 9999;
		
		for(int i = 0; i < 138; i++) {
			int q = pal_list[i].power;
			int ldif = p < q ? q - p : p - q;
			
			int skp_flg = 0;
			
			for(int j = 0; j < 28; j++) {
				if(uniq_bleed[j*3+0] == pal_list[i].idx) skp_flg = 1;
			}
			
			if(skp_flg) continue;
			
			if(dif > ldif || (dif == ldif && iid >= pal_list[i].idx)) {
				dif = ldif;
				idx = i;
				iid = pal_list[i].idx;
			}
		}
		
		bleed_table[p] = idx;
	}
}

int bleed(int a, int b) {
	int idx_a = pal_list[a].idx;
	int idx_b = pal_list[b].idx; 
	
	for(int i = 0; i < 28; i++) {
		if((uniq_bleed[i*3+1] == idx_a && uniq_bleed[i*3+2] == idx_b) || (uniq_bleed[i*3+1] == idx_b && uniq_bleed[i*3+2] == idx_a)) {
			int ridx = uniq_bleed[i*3+0];
			
			for(int i = 0; i < 138; i++) {
				if(pal_list[i].idx == ridx) return i;
			}
		}
	}
	
	int r = (pal_list[a].power + pal_list[b].power) / 2;
	
	return bleed_table[r];
};

int abs_base = 0;

int get_pal(int target) {
	for(int i = 0; i < 138; i++) {
		if(pal_list[i].power == target) return i;
	}
	return -1;
}

void print_pal(int r) {
	printf("No.%d %s (Power %d)", pal_list[r].no, pal_list[r].name, pal_list[r].power);
}

void dump_result(int *res, int base, int target) {
	printf("## ");
	print_pal(target);
	printf("  \n");
	
	for(int i = 0; i < 138; i++) {
		if(res[i]) {
			printf("- ");
			print_pal(i);
			printf(" + ");
			print_pal(base);
			printf("  \n");
		}
	}
}

int search_pal(int idx_base, int idx_target, int gen, int maxgen, int *res) {
	int next_target_a[138] = { 0 };
	int next_target_b[138] = { 0 };
	
	int bleeded_count = 0;
	
	for(int i = 0; i < 138; i++) {
		for(int j = 0; j < 138; j++) {
			if(i == idx_target || j == idx_target) continue;
			
			int r = bleed(i, j);
			
			if(r == idx_target && (i == idx_base || j == idx_base)) {
				res[i == idx_base ? j : i] = 1;
				bleeded_count++;
			} else if (r == idx_target && i != idx_base && j != idx_base) {
				next_target_a[i] = 1;
				next_target_b[i] = j;
			}
		}
	}
	
	
	/*if(gen == maxgen) return bleeded_count;
	
	int cres[138][138];
	int ccount[138];
	
	printf("# %d-Gen Combo\n", gen + 2);
	
	for(int i = 0; i < 138; i++) {
		if(next_target_a[i]) {
			printf("- ");
			print_pal(i);
			puts("");
		}
	}
	
	int search_list[138];
	int search_cnt = 0;
	
	for(int i = 0; i < 138; i++) {
		if(next_target_a[i]) {
			search_list[search_cnt] = i;
			search_cnt++;
		}
	}*/
	
	/*
#pragma omp parallel for
	for(int k = 0; k < search_cnt; k++) {
		int i = search_list[k];
		int j = next_target_b[i];
		memset(cres[i], 0, 138 * sizeof(int));
		
		ccount[i] = search_pal(idx_base, i, gen + 1, maxgen, cres[i]);
	}
	
	puts("");
	
	for(int i = 0; i < 138; i++) {
		if(ccount[i] > 0) {
			dump_result(cres[i], idx_base, i);
			puts("");
		}
	}
	
	puts("");*/
	
	return bleeded_count;
}

int main(int argc, char *argv[]) {
	int maxgen = atoi(argv[1]);
	int target = atoi(argv[2]);
	int base = atoi(argv[3]);
	
	if(argc > 4) abs_base = atoi(argv[4]);
	
	int idx_base = get_pal(base);
	int idx_target = get_pal(target);
	
	create_table();
	
	int res[138] = { 0 };
	int cnt;
	
	cnt = search_pal(idx_base, idx_target, 0, maxgen, res);
	
	puts("# Gen T+0");
	dump_result(res, idx_base, idx_target);
	puts("");
	
	for(int j = 0; j < maxgen; j++) {
		printf("# Gen T-%d\n", j + 1);
		
		int res2[138] = { 0 };
		
		for(int i = 0; i < 138; i++) {
			int res3[138] = { 0 };
			if(res[i]) {
				cnt = search_pal(idx_base, i, 0, maxgen, res3);
				dump_result(res3, idx_base, i);
				
				for(int j = 0; j < 138; j++) {
					res2[j] |= res3[j];
				}
				
				puts("");
			}
		}
		
		memcpy(res, res2, 138 * sizeof(int));
	}
	
	return 0;
};
