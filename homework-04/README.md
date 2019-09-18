##WordsSearch生成，验证工具

new.c		:读入words.txt 生成 result.txt 

test.c		:读入（默认读入sample.txt 需要指定参数伟result.txt） 屏幕生成测试结果说明

words.txt	:第一行一个整数n，表示以下有n行单词

result.txt	:new生成的结果，第一行一个整数n，以下n行单词，最后输出一个矩阵

sample.txt	:老师网站上的例子

new			:new.c的可执行文件(under linux)

##new.c使用方法

>gcc new.c -o new

>./new 18 18 #生成18\*18的结果矩阵（有很小的几率出错）

目前可以生成的最优矩阵为18\*18

	JE MCRASH    CTP  
	P SPUDESKTOPFEHR  
	EHCACLPV REVIRDIO 
	GIGABYTERAWDRAHNPP
	 SFHWABI EKAEW TU 
	LADA  TEM SSWEPEP 
	LVRCQXHAREICIEERL 
	OEOK UTYDSDIRRMAO 
	RUWE NDPNRPIEFOFAM
	CESR IIOAOPAA TLDE
	SLSE LWCWHIACUIODD
	MIAWR D ENVTPECPRO
	IFP ONNRUALNUUOEAM
	LP FURASJJIOMLNNO 
	EI OULBMUO EASOIB 
	YZSNTOOBERN BD SY 
	  ETHERNETIQUETTE 
	 M  WINDOWSVG   KR

	test  result from my test.c

	STATE1:	is good!
	J E   M C-R-A-S-H         C T P     
	|  \   \   \               \ \|     
	P   S P U D-E-S-K-T-O-P F E H R     
	|    X   \   X          | |  \|\    
	E-H-C-A-C L P V   R-E-V-I-R-D I O   
	|  /   \ \ X   \        | |   |\ \  
	G-I-G-A-B-Y-T-E-R-A-W-D-R-A-H N P P 
	         X \ \   \      | |   |     
	  S F H W A B I   E K A E W   T U   
	  |  \|/   \ \ \   \| | | |   H |   
	L A D A     T E M   S S W E P E P   
	| | |/|\     \ \ \  | | | |/  H |   
	L V R C Q X H A R E I C I E E R L   
	| |/| |   | |  \ \|\| | |/| | | |   
	O E O K   U T Y D S D I R R M A O   
	|   | |   | | |   |X \|/| | | | |   
	R U W E   N D P N R P I E F O F A M 
	|\ \| |   | |\|  X|  X \    | | | | 
	C E S R   I I O A O P A A   T L D E 
	| |\|\    | | |X  |X   \   /| |/  | 
	S L S E   L W C W H I A C U I O D D 
	| | |\ \    |/   X|  X  |X  |/H | | 
	M I A W R   D   E N V T P E C P R O 
	| | |  \ \ /|  /  |X   X|  /| | | | 
	I F P   O N N R U A L N U U O E A M 
	| |      X \|/ / /|  X   X  | | |   
	L P   F U R A S J J I O M L N N O   
	| |   |/   X|X \  |    X   \    |   
	E I   O U L B M U O   E A S-O-I-B   
	| |  /|/     \ \ \|  /   \   \  |   
	Y Z S N T-O-O-B-E-R N   B D   S Y   
	     /|        \  |X    |      \|   
	    E-T-H-E-R-N=E=T-I-Q-U-E-T-T-E   
	   /             \   \  |       |\  
	  M     W-I-N-D-O-W-S V G       K R 

	STATE2:	is good! n&m = 18

	STATE3:	is good!


##test.c使用方法
输出结果显示是否满足1，2，3条件

	1、每个单词只出现且必须出现一次、没空行空列
	2、长宽必须一样
	3、四个角必须被单词包含

对于sample.txt文件，输出：


	STATE1:	is good!
	J-P-E-G E M H-T-D-I-W-D-N-A-B I X I M 
	     \   \   /                  | | | 
	C E E R R S N D C-A-C-H-E E B-S-U N E 
	  | | |\   X   \   \   /  |     | | | 
	D V M E A O R O R W V R P R Y T N P D 
	 \| | |  X   \   X   X    | | | | | | 
	D A O K F W C O E O A A I A E E I U O 
	| |\| |    X|  X   X   X  | | | | | | 
	O S T C U P Y B H W W I J W L R L T M 
	|   |\|  X  |X   X   X    | | | | |   
	W P I A U N B P E N C S D D I A A E D 
	| |\| |\   X|  X   X   X  | | | | | | 
	N O C H B R E E S S A A S R M F R N O 
	| | |\   X  |X   /   X   \| | | | | | 
	L T O I O A R M A R O J N A S L E R C 
	| | |  /   X|      /   X  |\  | | | | 
	O K N W C F S O N L D O O H P O H E U 
	| |  /   X  |\   X   X   \    | | | | 
	A S S F A R P E P E I R E R P P P H M 
	| |/|  X   X|  /   X   X   X    | | | 
	D E W Q I O A U U T T L A R T R I T E 
	 /| |    X  |\ / /   X   X   /  | | | 
	R D O V R R C S U S I I I C E N R E N 
	  | |  X   X|/ X   X   X   X   \|   | 
	S R D T I O E L H F C N Q B D P E C T 
	| | |    X / X   /   X   X   X  |\    
	E I N E P R O W P G T R O U I N P P S 
	| | |  / / X   X   X   X   X   \   X  
	R V I Y N S U I I E U O O H E D U O O 
	| | |  / /   X   X   X   X   \ \ X    
	V E W A E S Z S R R T B C L S T I O O 
	| |  / /           \       \   X \ \  
	E R M R M-U-L-T-I-M-E-D-I-A L B T S S 
	|  /                             \ \  
	R E G-I-G-A-B-Y-T-E R D-R-A-O-B-Y-E-K 

	STATE2:	bad! n=18 m=19

	STATE3:	is good!

