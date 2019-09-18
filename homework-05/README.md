##接口声明
###主要接口
/reg

	GET:

		输出一个注册表单,其中

		id:用户名

		pd:密码

	POST:

		接收一个表单{id="",pd=""}，返回：

		0:注册成功

		-1:注册失败

/attend

	GET:

		输出一个游戏参与表单，其中

		id:用户名

		pd:密码

		num:1-100之间的实数，表示所要提交的数字

	POST:

		接受一个表单(id="",pd="",num="")，返回:

		-1:用户名不存在

		-2:密码错误

		-3:数字范围出错(必须在1-100之间)

		left_time+","+now_turn+","+success?:

			left_time:表示下一轮多少秒后开始

			now_turn:当前轮数

			success?:1表示提交成功，0表示提交失败(服务器锁中，正在计算)

/result

	GET:

		返回n行，倒序的golden_number

/

	GET:

		返回综合信息榜

##设计说明

http处理使用webpy框架实现，主要分为url映射和http请求处理。
	
http请求处理使用如上规范，能满足基本游戏要求。	

测试时使用2s进行一次游戏，一共40个客户端，能满足基本要求。

在综合信息榜使用了ajax异步通讯方法，来提高显示效率。

绘制goldennumber时使用了html5元素canvas，来动态显示最近40次游戏的golden number变化趋势。
