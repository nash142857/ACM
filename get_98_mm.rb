#encoding: utf-8
require 'mechanize'
require 'net/http'
require 'open-uri'
LOGIN_URL = "http://www.cc98.org"
MM_URL = "http://www.cc98.org/list.asp?boardid=146"
NAME = "******"
PASSWORD = "****"
class Catchmm
  attr_accessor :agent
  def initialize(url, name, password)
    @agent = Mechanize.new
    @agent.user_agent_alias = 'Linux Mozilla'
    page = @agent.get("http://www.cc98.org")
    form = page.forms.first
    form.field_with(:name => 'username').value = "nash142857"
    form.field_with(:type => 'password').value = "936866"
    res = form.click_button
  end
  def get_pic(url, dirname)
    dir = "/home/gsl/mm/" + dirname
    if(!Dir.exist?(dir))
     Dir.mkdir(dir)
    else
     return
    end
    res = agent.get(url)
    pattern = /\[upload=(png|jpg)(,1)?\](.*?)\[\/upload\]/
    photo_urls = res.body.scan(pattern).map {|x| x[2]}
    threads = []
    Dir.chdir(dir) do
      photo_urls.each do |photo_url|  
       agent.get(photo_url) do |photo|
          puts "save:#{photo_url}"
          photo.save
       end
      end
    end
  end
  def get_mm_link(url)
    page = agent.get(url)
    page.links_with(:dom_id => /topic_(.*?)/).each do |link|
     get_pic("http://www.cc98.org/"+link.href,link.text)
    end
  end
end
catcher = Catchmm.new(LOGIN_URL,NAME, PASSWORD)
catcher.get_mm_link(MM_URL)
