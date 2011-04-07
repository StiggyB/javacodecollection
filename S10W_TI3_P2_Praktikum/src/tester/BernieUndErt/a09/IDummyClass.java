package tester.BernieUndErt.a09;

import javax.management.DescriptorKey;

/**
 * Interface zu unserer DummyClass.
 * 
 * @author Bernie und Ert
 * @version 0.1beta
 */
@MyAnnotation(name = "MeineIFaceAnnotation", value = "123456")
interface IDummyClass {

	public abstract Integer getPrivateInteger();

	public abstract void setPrivateInteger(Integer privateInteger);

	@Deprecated
	@DescriptorKey(value = "1337")
	public abstract Integer getPublicInteger();

	@Deprecated
	public abstract void setPublicInteger(Integer publicInteger);

}