package br.inatel.inventory.model;

//A classe está em final porque ela não vai ser extendida

public final class Item{

	private Integer idItem;
	private String nameItem;
	private Integer qtItem;
	private String descriptionItem;
	
	
	public Integer getIdItem() {
		return idItem;
	}
	public void setIdItem(Integer idItem) {
		this.idItem = idItem;
	}
	public String getNameItem() {
		return nameItem;
	}
	public void setNameItem(String nameItem) {
		this.nameItem = nameItem;
	}
	public Integer getQtItem() {
		return qtItem;
	}
	public void setQtItem(Integer qtItem) {
		this.qtItem = qtItem;
	}
	public String getDescriptionItem() {
		return descriptionItem;
	}
	public void setDescriptionItem(String descriptionItem) {
		this.descriptionItem = descriptionItem;
	}
	
}
