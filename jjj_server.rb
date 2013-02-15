require 'serialport'
require 'sinatra'
require 'rack-flash'
require 'sinatra/redirect_with_flash'
require_relative 'jjj_arduino'

#setup
enable :sessions
use Rack::Flash

set :arduino, JJJArduino.new

#Routes
get '/' do
  erb :index
end

get '/broadcast' do
  erb :broadcast
end

get '/countdown' do
  settings.arduino.send_count
  @song_count = settings.arduino.song_count
  erb :countdown
end

post '/set_count' do
  action = params[:action]

  if action == "increment"
   settings.arduino.increment_count
  elsif action == "decrement"
    settings.arduino.decrement_count
  end

  redirect '/countdown'
end

post '/message' do
  settings.arduino.send_message params[:message]
  redirect '/broadcast', :notice => 'Your broadcast has been sent.'
end