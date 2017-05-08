package prod_cons;

public class Consumer extends Thread{
	
	private Production temp;
	
	public Consumer(Production product){
		temp = product;
	}
	
	public void run(){
		
		for(int i = 0; i < 10; i++)
			temp.cons();
		
	}
}
