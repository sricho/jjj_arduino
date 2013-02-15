class JJJArduino
  START_MESSAGE = 33.chr
  START_COUNT = 37.chr

  COUNT_MAXIMUM = 100
  COUNT_MINIMUM = 1

  attr_reader :song_count

  def initialize
    @port = SerialPort.new( '/dev/cu.usbmodemfa131', 9600 ) || {}
    @song_count = COUNT_MAXIMUM
    set :song_count, @song_count
    self.send_count
  end

  def send_message(message = "None")
    @port.puts [ START_MESSAGE, message ].join
  end

  def send_count
    @port.puts [ START_COUNT, @song_count ].join
  end

  def increment_count
    settings.song_count = settings.song_count + 1 if @song_count < COUNT_MAXIMUM
    @song_count = settings.song_count
  end

  def decrement_count
    settings.song_count = settings.song_count - 1 if @song_count > COUNT_MINIMUM
    @song_count = settings.song_count
  end
end