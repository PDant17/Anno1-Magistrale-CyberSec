public class Message {
	private String uid, temperature, humidity, flame, current, co2;
	public String getCo2() {
		return co2;
	}

	public void setCo2(String co2) {
		this.co2 = co2;
	}

	private LSM6DSOXTR lsm6dsoxtr;
	
	public static class LSM6DSOXTR {
		private String x, y, z;

		public String getX() {
			return x;
		}

		public void setX(String x) {
			this.x = x;
		}

		public String getY() {
			return y;
		}

		public void setY(String y) {
			this.y = y;
		}

		public String getZ() {
			return z;
		}

		public void setZ(String z) {
			this.z = z;
		}

		public LSM6DSOXTR(String x, String y, String z) {
			super();
			this.x = x;
			this.y = y;
			this.z = z;
		}

		@Override
		public String toString() {
			return "LSM6DSOXTR [x=" + x + ", y=" + y + ", z=" + z + "]";
		}
	}

	public String getTemperature() {
		return temperature;
	}

	public void setTemperature(String temperature) {
		this.temperature = temperature;
	}

	public String getHumidity() {
		return humidity;
	}

	public void setHumidity(String humidity) {
		this.humidity = humidity;
	}

	public String getFlame() {
		return flame;
	}

	public void setFlame(String flame) {
		this.flame = flame;
	}

	public String getCurrent() {
		return current;
	}

	public void setCurrent(String current) {
		this.current = current;
	}

	public LSM6DSOXTR getLsm6dsoxtr() {
		return lsm6dsoxtr;
	}

	public void setLsm6dsoxtr(LSM6DSOXTR lsm6dsoxtr) {
		this.lsm6dsoxtr = lsm6dsoxtr;
	}

	public Message(String uid, String temperature, String humidity, String flame, String current, String co2,
			LSM6DSOXTR lsm6dsoxtr) {
		super();
		this.uid = uid;
		this.temperature = temperature;
		this.humidity = humidity;
		this.flame = flame;
		this.current = current;
		this.co2 = co2;
		this.lsm6dsoxtr = lsm6dsoxtr;
	}

	public String getUid() {
		return uid;
	}

	public void setUid(String uid) {
		this.uid = uid;
	}

	public String get(String title) {
		if(title.equals("Temperature")) 
			return getTemperature();
		else if (title.equals("Humidity")) 
			return getHumidity();
		else if (title.equals("Flame")) 
			return getFlame();
		else if (title.equals("Current")) 
			return getCurrent();
		else if (title.equals("Co2")) 
			return getCo2();
		return null;
	}

	@Override
	public String toString() {
		return "Message [uid=" + uid + ", temperature=" + temperature + ", humidity=" + humidity + ", flame=" + flame
				+ ", current=" + current + ", co2=" + co2 + ", lsm6dsoxtr=" + lsm6dsoxtr + "]";
	}
	
}
