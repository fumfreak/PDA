package prod_cons;

public class Production {
	
	private boolean available = false;
	private int container_prod = 0;
	private int container_cons = 0;
	
	public synchronized void prod(){
		
		if(available){
			
			try{
				wait();
			}
			catch(InterruptedException e){
				System.out.println("Eroare la productie");
			}
		}
		available = true;
		container_prod++;
		System.out.println(container_prod+" produse valabile");
		notifyAll();
	}
	
	public synchronized void cons(){
		
		if(available == false){
			try{
				wait();
			}
			catch(InterruptedException e){
				System.out.println("Eroare de consum");
			}
		}
		available = false; 
		container_cons++;
		System.out.println(container_cons+" produse consumate");
		notifyAll();
		
	}
}