require 'spec_helper'

describe DogController do

  #Delete these examples and add some real ones
  it "should use DogController" do
    controller.should be_an_instance_of(DogController)
  end


  describe "GET 'bark'" do
    it "should be successful" do
      get 'bark'
      response.should be_success
    end
  end

  describe "GET 'fetch'" do
    it "should be successful" do
      get 'fetch'
      response.should be_success
    end
  end
end
