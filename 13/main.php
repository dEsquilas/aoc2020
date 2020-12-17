<?php
$input = trim(str_replace("\r","",file_get_contents("input")));
$lines = explode("\n",$input);
$buses = explode(",",$lines[1]);
$n = 0;
$inc = (int)$buses[0];

for($t=1;$t<sizeof($buses);$t++){
	if($buses[$t] == "x") continue;
	$first = 0;
	while(true) {
		$bus = (int)$buses[$t];
		if(floor(($n+$t)/$bus) == ($n+$t)/$bus) {
			echo "{$t}|{$bus}|" . floor(($n+$t)/$bus) . "\n";
			if($first == 0) {
				if($t == sizeof($buses) -1) {
					//final entry - STOP
					echo "{$n}\n";
					exit;
				}
				$first = $n;
			}
			else {
				$inc = $n - $first;
				break;
			}
		}
		$n+=$inc;
	}
}