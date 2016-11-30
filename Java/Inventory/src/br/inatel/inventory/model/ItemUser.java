package br.inatel.inventory.model;

//A classe está em final porque ela não vai ser extendida

public final class ItemUser {

	private Integer idItemUser;
	private User user;
	private Item item;
	private String dateOut;
	private String dateIn;
	private Integer qtItemUser;
	
	
	public Integer getIdItemUser() {
		return idItemUser;
	}
	public void setIdItemUser(Integer idItemUser) {
		this.idItemUser = idItemUser;
	}
	public User getUser() {
		return user;
	}
	public void setUser(User user) {
		this.user = user;
	}
	public Item getItem() {
		return item;
	}
	public void setItem(Item item) {
		this.item = item;
	}
	public String getDateOut() {
		return dateOut;
	}
	public void setDateOut(String dateOut) {
		this.dateOut = dateOut;
	}
	public String getDateIn() {
		return dateIn;
	}
	public void setDateIn(String dateIn) {
		this.dateIn = dateIn;
	}
	public Integer getQtItemUser() {
		return qtItemUser;
	}
	public void setQtItemUser(Integer qtItemUser) {
		this.qtItemUser = qtItemUser;
	}
	
}
