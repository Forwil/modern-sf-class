require "net/http"
params = Hash.new
params[:id] = ARGV[0]
params[:pd] = ARGV[1]
addr = "http://localhost"
uri = URI.parse(addr + "/reg")
res = Net::HTTP.post_form(uri, params)

while true
	params[:num] = rand(100) + 1
	uri = URI.parse(addr + "/attend")
	res = Net::HTTP.post_form(uri, params)
	str = res.body.split(/,/)
	
	time = str[0].to_f
	puts  time
	sleep(time)
end
