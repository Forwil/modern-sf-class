		var NOWB = -1;
		var SPEED = 0;
		var set_color = function(i,j,co){
			if (co!="" && i<n && j<m){
				document.getElementById("table").rows[i].cells[j].style.background = co;
			}
		}

		var set_border = function(i,j,st){
			if (st!="" && i<n && j<m){
				document.getElementById("table").rows[i].cells[j].style.border = st;
			}
		}	
		var get_json = function(){
			var xmlhttp = new XMLHttpRequest();
			xmlhttp.open("GET",window.location.href+"history",false);
			xmlhttp.send();
			HIS = eval("(" +xmlhttp.responseText+")");
			n = document.getElementById("table").rows.length;
			m = document.getElementById("table").rows[0].cells.length;
			return true;
		}
		var draw = function(x,w,co,bo){
			var i,j,a,b,c,d;
			a = HIS[x][w]['a'];
			b = HIS[x][w]['b'];
			c = HIS[x][w]['c'];
			d = HIS[x][w]['d'];
			i = a -1;
			do{
				j = b -1;
				i = (i + 1)%n;
				do{
					j = (j + 1)%m;
					set_color(i,j,co);
					set_border(i,j,bo);
				}while(j!=d);
			}while(i!=c);
			if (NOWB!=-1){
				document.getElementById(w).innerHTML = HIS[x][w]['sum'];
			}
		}

		var renew = function(){
			var i,j;
			for(i=0;i<n;i++)
				for(j=0;j<m;j++)
				{
					set_color(i,j,'white');
					set_border(i,j,'2px dotted black');
				}
		}

		var draw_it = function(){
			var i,j;
			renew();
			if(NOWB>=0){
				draw(NOWB,'now',"#AAAAAA","");
				draw(NOWB,'max',"","2px solid blue");
			}
		}
		
		var draw_next = function(){
			if(NOWB < HIS.length-1){
				NOWB += 1;
			}else{
				SPEED = 0;
			}
			draw_it();
			document.getElementById("step").innerHTML = NOWB+1;
		}
	
		var draw_last = function(){
			if(NOWB>=0){
				NOWB -= 1;
			} else{
				SPEED = 0;
			}
			draw_it();
			document.getElementById("step").innerHTML = NOWB+1;
		}
		
		var auto_go = function(){
			if (SPEED>0){
				draw_next();
			}
			else if (SPEED<0){
				draw_last();
			}
			if (SPEED){
				setTimeout("auto_go()",1000/Math.abs(SPEED));
			}
		}	

		var stop = function(){
			SPEED = 0;
			document.getElementById("speed").innerHTML = SPEED;
		}
	
		var go	= function(x){
			if (SPEED == 0){
				SPEED = x;
				auto_go();
			}else{
				SPEED += x;
			}
			document.getElementById("speed").innerHTML = SPEED;
		}
		
		var check = function(){
			var hsize = document.getElementById("hsize").value;
			var	lsize = document.getElementById("lsize").value; 
			var low	  = document.getElementById("low").value;
			var hig	  = document.getElementById("hig").value;
			if (hsize<=0 || lsize <=0 || low>hig || hsize >50 || lsize > 50){
				alert("Number your input isn't available!")
				return false;
			}
			return true;
		}
